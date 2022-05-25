#ifndef GALAMENT_SERVER_WEBSOCKET_SERVER_H
#define GALAMENT_SERVER_WEBSOCKET_SERVER_H

#include "client.h"

#include <map>

namespace galament::server::websocket {

class MessageHandler;

class Server {
public:
	using WebsocketppServer = websocketpp::server<websocketpp::config::asio>;
	using MessagePtr = WebsocketppServer::message_ptr;

	Server(MessageHandler& message_handler);

	void Run(uint16_t port);

private:
	WebsocketppServer server_;
	std::map<
		websocketpp::connection_hdl, 
		ClientPtr,
		std::owner_less<websocketpp::connection_hdl> > clients_;
	boost::asio::io_service io_service;
	MessageHandler& message_handler_;

	void Initialize();

	void OnOpen(websocketpp::connection_hdl hdl);
	void OnClose(websocketpp::connection_hdl hdl);
	void OnMessage(websocketpp::connection_hdl hdl, MessagePtr message);
	void OnPongTimeout(websocketpp::connection_hdl hdl, std::string);
};

class MessageHandler {
public:
	virtual ~MessageHandler() = default;

	virtual void OnMessage(ClientPtr, const std::string &) {};
};

} // namespace galament::server::websocket

#endif