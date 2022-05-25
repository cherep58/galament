#include "command_executor.h"

#include <condition_variable>

namespace galament::server::command {

CommandExecutor::CommandExecutor(CommandQueue& queue)
	: queue_(queue)
	, execute_thread_(std::bind(&CommandExecutor::ExecuteLoop, this))
{
	execute_thread_.detach();
}

void CommandExecutor::RegisterExecutor(CommandType type, executor::ExecutorPtr executor)
{
	executors_[type] = std::move(executor);
}

void CommandExecutor::Notify()
{
	execute_condition_.notify_one();
}

[[noreturn]] void CommandExecutor::ExecuteLoop()
{
	while (true) {
		while (queue_.IsEmpty()) {
			std::unique_lock<std::mutex> lock(queue_.mutex());
			execute_condition_.wait(lock);
			lock.unlock();
		}

		Execute(std::move(queue_.Pop()));
	}
}

void CommandExecutor::Execute(CommandPtr command)
{
	auto it = executors_.find(command->type());
	if (it != executors_.end()) {
		it->second->Execute(std::move(command));
	}
}

} // namespace galament::server::command
