#ifndef GALAMENT_COMMON_MESSAGE_MESSAGE_SERIALIZER_H
#define GALAMENT_COMMON_MESSAGE_MESSAGE_SERIALIZER_H

#include "message_visitor.h"

#include "common/message/message_type.h"
#include "common/data_types/data_packet.h"
#include "common/data_types/statistic.h"

#include <string>

namespace galament::common::message {

class MessageSerializer {
public:
	virtual std::string Serialize(const data_types::DataPacket& data_packet) = 0;
	virtual std::string Serialize(const data_types::Statistic& statistic) = 0;
	virtual std::string SerializeWithoutPayload(message::MessageType message_type) = 0;

	virtual bool Unserialize(std::string_view message, MessageVisitor& visitor) = 0;
};

} // galament::common::message

#endif
