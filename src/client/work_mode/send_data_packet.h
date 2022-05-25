#ifndef GALAMENT_CLIENT_WORK_MODE_SEND_DATA_PACKET_H
#define GALAMENT_CLIENT_WORK_MODE_SEND_DATA_PACKET_H

#include "abstract.h"
#include "websocket/client.h"
#include "helper/random_generator.h"

#include "common/data_types/data_packet.h"
#include "common/protobuf/message_serializer.h"

#include "boost/asio.hpp"

namespace galament::client::work_mode {

class SendDataPacket : public Abstract, websocket::EventsHandler {
public:
    SendDataPacket(std::string_view address);

    void Run() override;

    void OnOpen(const websocket::Client::Connection& connection) override;
    void OnFail(const websocket::Client::Connection& connection) override;

private:
    boost::asio::io_service io_service;
    boost::asio::steady_timer timer_;

    common::data_types::DataPacket data_packet_;
    websocket::Client client_;
    common::protobuf::MessageSerializer serializer_;

    helper::RandomGenerator random_generator_;

    bool reconnect_ = false;

    void InitializeSendTimer();
    void Send(const boost::system::error_code& ec);
};

} // namespace galament::client::work_mode

#endif