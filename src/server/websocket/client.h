#ifndef GALAMENT_SERVER_WEBSOCKET_CLIENT_H
#define GALAMENT_SERVER_WEBSOCKET_CLIENT_H

#include "common/websocket/connection.h"

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "boost/asio.hpp"

namespace galament::server::websocket {

class Client {
public:
	using WebsocketppServer = websocketpp::server<websocketpp::config::asio>;
	using Connection = common::websocket::Connection<WebsocketppServer::connection_ptr>;

	Client(WebsocketppServer::connection_ptr connection, boost::asio::io_service &io_service);

	Connection connection() const;

	void InitializePingTimer();

private:
	WebsocketppServer::connection_ptr connection_;
	boost::asio::steady_timer ping_timer_;

	void Ping(const boost::system::error_code& ec);
};

using ClientPtr = std::shared_ptr<Client>;

} // namespace galament::server::websocket

#endif