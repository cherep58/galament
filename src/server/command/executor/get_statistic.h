#ifndef GALAMENT_SERVER_COMMAND_EXECUTOR_GET_STATISTIC_H
#define GALAMENT_SERVER_COMMAND_EXECUTOR_GET_STATISTIC_H

#include "abstract.h"

#include "database/database.h"
#include "common/message/message_serializer.h"

namespace galament::server::command::executor {

class GetStatistic : public Abstract {
public:
	GetStatistic(database::Database& db, common::message::MessageSerializer& message_serializer);

	void Execute(const CommandPtr &command) override;

private:
	database::Database& db_;
	common::message::MessageSerializer& message_serializer_;
};

} // namespace galament::server::command::executor

#endif