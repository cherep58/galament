#include "save_data_packet.h"

#include "command/command/save_data_packet.h"

namespace galament::server::command::executor {

SaveDataPacket::SaveDataPacket(database::Database& db)
	: db_(db)
{
	;
}

void SaveDataPacket::Execute(const CommandPtr &command)
{
	db_.SaveDataPacket(dynamic_cast<command::SaveDataPacket*>(command.get())->data_packet());
}

} // namespace galament::server::command::executor