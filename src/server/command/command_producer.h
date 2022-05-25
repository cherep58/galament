#ifndef GALAMENT_SERVER_COMMAND_COMMAND_PRODUCER_H
#define GALAMENT_SERVER_COMMAND_COMMAND_PRODUCER_H

#include "command/abstract.h"
#include "command_queue.h"

#include "common/message/message_visitor.h"

namespace galament::server::command {

class CommandProducer : public common::message::MessageVisitor {
public:
	CommandProducer(CommandQueue& queue);

	void set_client(websocket::ClientPtr client_);

	void Visit(const common::data_types::DataPacket& data_packet) override;
	void VisitStatisticRequest() override;

private:
	CommandQueue& queue_;
	websocket::ClientPtr client_;
};

} // namespace galament::server::command

#endif