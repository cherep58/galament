#ifndef GALAMENT_SERVER_DATABASE_DATABASE_H
#define GALAMENT_SERVER_DATABASE_DATABASE_H

#include "SQLiteCpp/Database.h"
#include "common/data_types/data_packet.h"
#include "common/data_types/statistic.h"

#include <filesystem>
#include <memory>
#include <string_view>

namespace galament::server::database {

class Database {
public:
	Database() = default;
	Database(const Database&) = delete;

	Database operator=(const Database&) = delete;

	bool Initialize(const std::filesystem::path& db_path);

	bool SaveDataPacket(const common::data_types::DataPacket& data_packet);
	bool GetStatistic(const common::data_types::Timestamp &now, 
		              const common::data_types::Timestamp &last1minute,
		              const common::data_types::Timestamp &last5minute,
		              common::data_types::Statistic& statistic);

private:
	std::unique_ptr<SQLite::Database> database_;

	bool CreateStructure();
};

} // namespace galament::server::database

#endif