#ifndef GALAMENT_SERVER_COMMAND_ABSTRACT_H
#define GALAMENT_SERVER_COMMAND_ABSTRACT_H

#include "command_type.h"

#include "websocket/client.h"

#include <memory>

namespace galament::server::command {

class Abstract {
public:
	Abstract(websocket::ClientPtr client);

	virtual ~Abstract() = default;

	virtual CommandType type() const = 0;

	const websocket::ClientPtr& client() const;

private:
	websocket::ClientPtr client_;
};

using CommandPtr = std::unique_ptr<Abstract>;

} // namespace galament::server::command

#endif