#ifndef GALAMENT_SERVER_COMMAND_COMMAND_EXECUTOR_H
#define GALAMENT_SERVER_COMMAND_COMMAND_EXECUTOR_H

#include "command/abstract.h"
#include "executor/abstract.h"
#include "command_queue.h"

#include <condition_variable>
#include <map>
#include <thread>

namespace galament::server::command {

class CommandExecutor {
public:
	CommandExecutor(CommandQueue& queue);

	void RegisterExecutor(CommandType type, executor::ExecutorPtr executor);

	void Notify();

private:
	std::condition_variable execute_condition_;
	std::map<CommandType, executor::ExecutorPtr> executors_;
	CommandQueue& queue_;
	std::thread execute_thread_;

	[[noreturn]] void ExecuteLoop();
	void Execute(CommandPtr command);
};

} // namespace galament::server::command

#endif