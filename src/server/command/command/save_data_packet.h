#ifndef GALAMENT_SERVER_COMMAND_SAVE_DATA_PACKET_H
#define GALAMENT_SERVER_COMMAND_SAVE_DATA_PACKET_H

#include "abstract.h"
#include "common/data_types/data_packet.h"

namespace galament::server::command {

class SaveDataPacket : public Abstract {
public:
	SaveDataPacket(websocket::ClientPtr client, const common::data_types::DataPacket &data_packet);

	CommandType type() const override;

	const common::data_types::DataPacket& data_packet();

private:
	common::data_types::DataPacket data_packet_;
};

} // namespace galament::server::command

#endif