#ifndef GALAMENT_SERVER_COMMAND_GET_STATISTIC_H
#define GALAMENT_SERVER_COMMAND_GET_STATISTIC_H

#include "abstract.h"

namespace galament::server::command {

class GetStatistic : public Abstract {
public:
	GetStatistic(websocket::ClientPtr client);

	CommandType type() const override;
};

} // namespace galament::server::command

#endif