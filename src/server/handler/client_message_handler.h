#ifndef GALAMENT_SERVER_HANDLER_CLIENT_MESSAGE_HANDLER_H
#define GALAMENT_SERVER_HANDLER_CLIENT_MESSAGE_HANDLER_H

#include "database/database.h"
#include "command/command_executor.h"
#include "command/command_producer.h"
#include "websocket/server.h"

#include "common/protobuf/message_serializer.h"

namespace galament::server::handler {

class ClientMessageHandler : public websocket::MessageHandler {
public:
	ClientMessageHandler(database::Database& db);

	void OnMessage(websocket::ClientPtr client, const std::string& payload) override;

private:
	command::CommandQueue command_queue_;
	command::CommandProducer command_producer_;
	command::CommandExecutor command_executor_;
	common::protobuf::MessageSerializer message_serializer_;
};

} // namespace galament::server::handler

#endif