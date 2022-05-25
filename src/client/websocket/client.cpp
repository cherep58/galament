#include "client.h"

namespace galament::client::websocket {

using namespace websocketpp;

constexpr std::string_view kWsProtocol = "ws://";

Client::Client(EventsHandler& events_handler, boost::asio::io_service* io_service)
    : events_handler_(events_handler)
{
	Initialize(io_service);
}

Client::Connection& Client::connection()
{
	return connection_;
}

void Client::Initialize(boost::asio::io_service* io_service)
{
#ifdef _DEBUG
	client_.set_access_channels(log::alevel::all);
	client_.set_error_channels(log::elevel::all);
#else
	client_.clear_access_channels(log::alevel::all);
	client_.clear_error_channels(log::elevel::all);
#endif

	using namespace websocketpp::lib;

	client_.set_message_handler([this](connection_hdl, MessagePtr msg) {
		events_handler_.OnMessage(connection_, msg->get_payload());
	});
	client_.set_open_handler([this](connection_hdl) {
		events_handler_.OnOpen(connection_);
	});
	client_.set_fail_handler([this](connection_hdl) {
		events_handler_.OnFail(connection_);
	});

	if (io_service != nullptr) {
		client_.init_asio(io_service);
	}
	else {
		client_.init_asio();
	}
}

void Client::Run(const std::string& address)
{
	auto uri = address;
	uri.insert(0, kWsProtocol);

	lib::error_code ec;
	WebsocketppClient::connection_ptr con = client_.get_connection(uri, ec);
	if (ec) {
		return;
	}

	connection_ = client_.connect(con);
	client_.run();
}

} // namespace galament::client::websocket