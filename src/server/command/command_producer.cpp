#include "command_producer.h"

#include "command/save_data_packet.h"
#include "command/get_statistic.h"

namespace galament::server::command {

using namespace galament::common::data_types;

CommandProducer::CommandProducer(CommandQueue& queue)
	: queue_(queue)
{
	;
}

void CommandProducer::set_client(websocket::ClientPtr client)
{
	client_ = std::move(client);
}

void CommandProducer::Visit(const DataPacket& data_packet)
{
	queue_.Push(std::make_unique<SaveDataPacket>(client_, data_packet));
}

void CommandProducer::VisitStatisticRequest()
{
	queue_.Push(std::make_unique<GetStatistic>(client_));
}

} // namespace galament::server::command
