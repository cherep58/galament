#include "get_statistic.h"

namespace galament::server::command {

GetStatistic::GetStatistic(websocket::ClientPtr client)
	: Abstract(client)
{
	;
}

CommandType GetStatistic::type() const
{
	return CommandType::kGetStatistic;
}

} // namespace galament::server::command
