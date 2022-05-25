#ifndef GALAMENT_SERVER_COMMAND_COMMAND_TYPE_H
#define GALAMENT_SERVER_COMMAND_COMMAND_TYPE_H

#include <cstdint>

namespace galament::server::command {

enum class CommandType : uint8_t {
	kUnknown = 0,
	kSaveDataPacket = 1,
	kGetStatistic = 2
};

} // namespace galament::server::command

#endif