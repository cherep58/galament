#ifndef GALAMENT_CLIENT_WEBSOCKET_CLIENT_H
#define GALAMENT_CLIENT_WEBSOCKET_CLIENT_H

#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "common/websocket/connection.h"

namespace galament::client::websocket {

class EventsHandler;

class Client {
public:
	using WebsocketppClient = websocketpp::client<websocketpp::config::asio_client>;
	using Connection = common::websocket::Connection<WebsocketppClient::connection_ptr>;
	using MessagePtr = WebsocketppClient::message_ptr;

	Client(EventsHandler &events_handler, boost::asio::io_service* io_service = nullptr);

	Connection& connection();

	void Run(const std::string &address);

private:
	WebsocketppClient client_;
	Connection connection_;
	EventsHandler& events_handler_;

	void Initialize(boost::asio::io_service *io_service);
};

class EventsHandler {
public:
	virtual ~EventsHandler() = default;

	virtual void OnOpen(const Client::Connection&) {};
	virtual void OnMessage(const Client::Connection&, const std::string &) {};
	virtual void OnFail(const Client::Connection&) {};
};

} // namespace galament::client::websocket

#endif