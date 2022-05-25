#include "client_message_handler.h"

#include "command/executor/save_data_packet.h"
#include "command/executor/get_statistic.h"

#include <thread>

namespace galament::server::handler {

using namespace galament::server::command;

ClientMessageHandler::ClientMessageHandler(database::Database& db)
	: command_producer_(command_queue_)
	, command_executor_(command_queue_)
{
	command_executor_.RegisterExecutor(CommandType::kSaveDataPacket, 
		std::make_unique<executor::SaveDataPacket>(db));
	command_executor_.RegisterExecutor(CommandType::kGetStatistic,
		std::make_unique<executor::GetStatistic>(db, message_serializer_));
}

void ClientMessageHandler::OnMessage(websocket::ClientPtr client, const std::string& payload)
{
	command_producer_.set_client(client);
	message_serializer_.Unserialize(payload, command_producer_);
	command_producer_.set_client(nullptr);

	command_executor_.Notify();
}

} // namespace galament::server::handler