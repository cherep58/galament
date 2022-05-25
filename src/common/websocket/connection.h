#ifndef GALAMENT_COMMON_WEBSOCKET_CONNECTION_H
#define GALAMENT_COMMON_WEBSOCKET_CONNECTION_H

#include <string_view>
#include <string>

#include "websocketpp/close.hpp"
#include "websocketpp/frame.hpp"

namespace galament::common::websocket {

template <class ConnectionPtr>
class Connection {
public:
	Connection() = default;
	Connection(ConnectionPtr connection) : connection_(connection) {};

	void SendBinary(std::string_view payload) const {
		connection_->send(payload.data(), payload.length(), websocketpp::frame::opcode::BINARY);
	}

	void Close(const std::string &reason = "") const {
		connection_->close(websocketpp::close::status::normal, reason);
	}

private:
	ConnectionPtr connection_;
};

} // galament::common::websocket

#endif
