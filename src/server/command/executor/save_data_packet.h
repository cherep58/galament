#ifndef GALAMENT_SERVER_COMMAND_EXECUTOR_SAVE_DATA_PACKET_H
#define GALAMENT_SERVER_COMMAND_EXECUTOR_SAVE_DATA_PACKET_H

#include "abstract.h"

#include "database/database.h"

namespace galament::server::command::executor {

class SaveDataPacket : public Abstract {
public:
	SaveDataPacket(database::Database& db);

	void Execute(const CommandPtr &command) override;

private:
	database::Database& db_;
};

} // namespace galament::server::command::executor

#endif