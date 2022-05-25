#ifndef GALAMENT_COMMON_PROTOBUF_MESSAGE_FACTORY_H
#define GALAMENT_COMMON_PROTOBUF_MESSAGE_FACTORY_H

#include "common/message/message_serializer.h"

namespace galament::common::protobuf {

class MessageSerializer : public message::MessageSerializer {
public:
	std::string Serialize(const data_types::DataPacket& data_packet) override;
	std::string Serialize(const data_types::Statistic& statistic) override;
	std::string SerializeWithoutPayload(message::MessageType message_type) override;

	bool Unserialize(std::string_view message, message::MessageVisitor& visitor) override;
};

} // galament::common::protobuf

#endif
