#include "get_statistic.h"

#include "command/command/save_data_packet.h"

namespace galament::server::command::executor {

using namespace std::chrono_literals;

GetStatistic::GetStatistic(database::Database& db, common::message::MessageSerializer& message_serializer)
	: db_(db)
	, message_serializer_(message_serializer)
{
	;
}

void GetStatistic::Execute(const CommandPtr &command)
{
	auto now = std::chrono::system_clock::now();

	common::data_types::Statistic statistic;
	if (!db_.GetStatistic(now, now - 1min, now - 5min, statistic)) {
		return;
	}

	command->client()->connection().SendBinary(message_serializer_.Serialize(statistic));
}

} // namespace galament::server::command::executor