#include "abstract.h"

namespace galament::server::command {

Abstract::Abstract(websocket::ClientPtr client)
	: client_(client)
{
	;
}

const websocket::ClientPtr& Abstract::client() const
{
	return client_;
}

} // namespace galament::server::command
