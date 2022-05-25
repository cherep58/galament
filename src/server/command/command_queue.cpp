#include "command_queue.h"

#include "command/get_statistic.h"

namespace galament::server::command {

using Lock = std::scoped_lock<std::mutex>;

std::mutex& CommandQueue::mutex()
{
	return mutex_;
}

void CommandQueue::Push(CommandPtr command)
{
	Lock lock(mutex_);

	commands_.push(std::move(command));
}

CommandPtr CommandQueue::Pop()
{
	Lock lock(mutex_);

	auto command = std::move(commands_.front());
	commands_.pop();
	return command;
}

bool CommandQueue::IsEmpty()
{
	Lock lock(mutex_);

	return commands_.empty();
}

} // namespace galament::server::command
