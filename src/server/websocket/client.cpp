#include "client.h"

namespace galament::server::websocket {

using namespace std::chrono_literals;

constexpr auto kPingInterval = 60s;
static std::string kPingPayload = "";

Client::Client(WebsocketppServer::connection_ptr connection, boost::asio::io_service& io_service)
	: connection_(connection)
	, ping_timer_(io_service)
{
	InitializePingTimer();
}

Client::Connection Client::connection() const
{
	return connection_;
}

void Client::InitializePingTimer()
{
	ping_timer_.expires_at(std::chrono::steady_clock::now() + kPingInterval);
	ping_timer_.async_wait(std::bind(&Client::Ping, this, std::placeholders::_1));
}

void Client::Ping(const boost::system::error_code& ec)
{
	if (ec) {
		return;
	}

	connection_->ping(kPingPayload);
}

} // namespace galament::server::websocket