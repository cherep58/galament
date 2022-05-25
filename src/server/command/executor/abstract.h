#ifndef GALAMENT_SERVER_COMMAND_EXECUTOR_ABSTRACT_H
#define GALAMENT_SERVER_COMMAND_EXECUTOR_ABSTRACT_H

#include "abstract.h"
#include "command/command/abstract.h"

namespace galament::server::command::executor {

class Abstract {
public:
	virtual ~Abstract() = default;

	virtual void Execute(const CommandPtr &command) = 0;
};

using ExecutorPtr = std::unique_ptr<Abstract>;

} // namespace galament::server::command::executor

#endif