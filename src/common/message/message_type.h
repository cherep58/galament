#ifndef GALAMENT_COMMON_MESSAGE_MESSAGE_TYPE_H
#define GALAMENT_COMMON_MESSAGE_MESSAGE_TYPE_H

#include <cstdint>

namespace galament::common::message {

enum class MessageType : uint8_t {
	kUnknown = 0,
	kDataPacked = 1,
	kStatisticRequest = 2,
	kStatisticResponse = 3
};

} // galament::common::message

#endif
