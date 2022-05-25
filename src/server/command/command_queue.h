#ifndef GALAMENT_SERVER_COMMAND_COMMAND_QUEUE_H
#define GALAMENT_SERVER_COMMAND_COMMAND_QUEUE_H

#include "command/abstract.h"

#include <queue>
#include <mutex>

namespace galament::server::command {

class CommandQueue {
public:
	std::mutex& mutex();

	void Push(CommandPtr);
	CommandPtr Pop();

	bool IsEmpty();

private:
	std::queue<CommandPtr> commands_;
	std::mutex mutex_;
};

} // namespace galament::server::command

#endif