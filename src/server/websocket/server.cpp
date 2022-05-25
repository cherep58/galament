#include "server.h"

namespace galament::server::websocket {

Server::Server(MessageHandler& message_handler)
	: message_handler_(message_handler)
{
	Initialize();
}

void Server::Run(uint16_t port)
{
	try {
		server_.listen(port);
		server_.start_accept();
	}
	catch (...) {
		return;
	}

	server_.run();
}

void Server::Initialize()
{
	using namespace websocketpp;

#ifdef _DEBUG
	server_.set_access_channels(log::alevel::all);
	server_.set_error_channels(log::elevel::all);
#else
	server_.clear_access_channels(log::alevel::all);
	server_.clear_error_channels(log::elevel::all);
#endif

	server_.set_reuse_addr(true);

	server_.set_open_handler(std::bind(&Server::OnOpen, this, std::placeholders::_1));
	server_.set_close_handler(std::bind(&Server::OnClose, this, std::placeholders::_1));
	server_.set_message_handler(
		std::bind(&Server::OnMessage, this, std::placeholders::_1, std::placeholders::_2));
	server_.set_pong_timeout_handler(
		std::bind(& Server::OnPongTimeout, this, std::placeholders::_1, std::placeholders::_2));

	server_.init_asio(&io_service);
}

void Server::OnOpen(websocketpp::connection_hdl hdl)
{
	clients_.emplace(hdl, std::make_shared<Client>(server_.get_con_from_hdl(hdl), io_service));
}

void Server::OnClose(websocketpp::connection_hdl hdl)
{
	auto it = clients_.find(hdl);
	if (it != clients_.end()) {
		clients_.erase(it);
	}
}

void Server::OnMessage(websocketpp::connection_hdl hdl, MessagePtr message)
{
	auto it = clients_.find(hdl);
	if (it != clients_.end()) {
		it->second->InitializePingTimer();
		message_handler_.OnMessage(it->second, message->get_payload());
	}
}

void Server::OnPongTimeout(websocketpp::connection_hdl hdl, std::string)
{
	server_.get_con_from_hdl(hdl)->close(websocketpp::close::status::going_away, "");
}

} // namespace galament::server::websocket