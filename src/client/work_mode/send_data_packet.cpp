#include "send_data_packet.h"

#include "common/protobuf/message_serializer.h"

#include <random>
#include <thread>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace galament::client::work_mode {

using namespace galament::client::websocket;
using namespace galament::common::protobuf;
using namespace std::chrono;

constexpr auto kMinSendInterval = 5s;
constexpr auto kMaxSendInterval = 30s;

constexpr float kMinXY = -90.0;
constexpr float kMaxXY = 90.0;

SendDataPacket::SendDataPacket(std::string_view address)
    : Abstract(address)
    , timer_(io_service)
    , client_(*this, &io_service)
{
    data_packet_.uuid() = random_generator_.GenerateUuid();
}

void SendDataPacket::OnOpen(const Client::Connection&)
{
    reconnect_ = true;

    InitializeSendTimer();
}

void SendDataPacket::OnFail(const Client::Connection&)
{
    timer_.cancel();
}

void SendDataPacket::InitializeSendTimer()
{
    auto send_interval = random_generator_.GenerateDuration(kMinSendInterval, kMaxSendInterval);
    timer_.expires_at(steady_clock::now() + send_interval);
    timer_.async_wait(std::bind(&SendDataPacket::Send, this, std::placeholders::_1));
}

void SendDataPacket::Send(const boost::system::error_code& ec)
{
    if (ec) {
        return;
    }

    data_packet_.set_dt(std::chrono::system_clock::now());
    data_packet_.set_x(random_generator_.GenerateReal(kMinXY, kMaxXY));
    data_packet_.set_y(random_generator_.GenerateReal(kMinXY, kMaxXY));

    client_.connection().SendBinary(serializer_.Serialize(data_packet_));

    InitializeSendTimer();
}

void SendDataPacket::Run()
{
    do {
        reconnect_ = false;

        std::thread client_thread(&Client::Run, &client_, std::cref(address_));
        client_thread.join();
    } while (reconnect_);
}

} // namespace galament::client::work_mode