#include "database.h"

#include <iostream>

namespace galament::server::database {

using namespace galament::common::data_types;

inline float GetFloat(const SQLite::Column& column)
{
	return static_cast<float>(column.getDouble());
}

bool Database::Initialize(const std::filesystem::path& db_path)
{
	try {
		database_ = std::make_unique<SQLite::Database>(db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		return CreateStructure();
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return false;
	}
}

bool Database::SaveDataPacket(const DataPacket& data_packet)
{
	if (!database_) {
		return false;
	}

	try {
		SQLite::Statement query(*database_.get(), R"(
			INSERT INTO data_packet (
				uuid,
				dt,
				x,
				y
			) VALUES (
				?,
				?,
				?,
				?
			)
		)");

		const auto &uuid = data_packet.uuid().Get();
		query.bind(1, uuid.data, static_cast<int>(uuid.size()));
		query.bind(2, ToUnixTimestamp(data_packet.dt()));
		query.bind(3, data_packet.x());
		query.bind(4, data_packet.y());

		query.exec();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

bool Database::GetStatistic(const Timestamp& now, const Timestamp& last1minute, const Timestamp& last5minute,
	                        Statistic& statistic)
{
	if (!database_) {
		return false;
	}

	try {
		SQLite::Statement query(*database_.get(), R"(
			SELECT 
				uuid,
				SUM(x_1),
				SUM(y_1),
				SUM(x_5),
				SUM(y_5)
			FROM (
				SELECT
					uuid,
					AVG(x) AS x_1,
					SUM(ABS(y)) AS y_1,
					0 AS x_5,
					0 AS y_5
				FROM data_packet
				WHERE dt BETWEEN ? AND ?
				GROUP BY uuid

				UNION ALL

				SELECT
					uuid,
					0 AS x_1,
					0 AS y_1,
					AVG(x) AS x_5,
					SUM(ABS(y)) AS y_5
				FROM data_packet
				WHERE dt BETWEEN ? AND ?
				GROUP BY uuid
			)
			GROUP BY uuid
		)");

		auto now_timestamp = ToUnixTimestamp(now);
		query.bind(1, ToUnixTimestamp(last1minute));
		query.bind(2, now_timestamp);
		query.bind(3, ToUnixTimestamp(last5minute));
		query.bind(4, now_timestamp);

		size_t rows_count = 0;
		for (; query.executeStep(); ++rows_count) {}
		query.reset();

		statistic.resize(rows_count);

		for (Statistic::iterator it = statistic.begin(); query.executeStep(); ++it) {
			auto uuid_column = query.getColumn(0);
			std::string_view uuid(reinterpret_cast<const char*>(uuid_column.getBlob()), uuid_column.getBytes());

			it->uuid().FromBinaryString(uuid);
			it->set_x_1min(GetFloat(query.getColumn(1)));
			it->set_y_1min(GetFloat(query.getColumn(2)));
			it->set_x_5min(GetFloat(query.getColumn(3)));
			it->set_y_5min(GetFloat(query.getColumn(4)));
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

bool Database::CreateStructure()
{
	try {
		database_->exec(R"(
			CREATE TABLE IF NOT EXISTS "data_packet" (
				"uuid"	BLOB NOT NULL COLLATE BINARY,
				"dt"	INTEGER NOT NULL,
				"x"	REAL NOT NULL,
				"y"	REAL NOT NULL
			);

			CREATE INDEX IF NOT EXISTS "dt" ON "data_packet" (
				"dt"	DESC
			);
		)");
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

} // namespace galament::server::database