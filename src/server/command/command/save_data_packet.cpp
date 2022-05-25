#include "save_data_packet.h"

namespace galament::server::command {

SaveDataPacket::SaveDataPacket(websocket::ClientPtr client, const common::data_types::DataPacket& data_packet)
	: Abstract(client)
	, data_packet_(data_packet)
{
	;
}

CommandType SaveDataPacket::type() const
{
	return CommandType::kSaveDataPacket;
}

const common::data_types::DataPacket& SaveDataPacket::data_packet()
{
	return data_packet_;
}

} // namespace galament::server::command