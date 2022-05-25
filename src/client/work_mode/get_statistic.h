#ifndef GALAMENT_CLIENT_WORK_MODE_GET_STATISTIC_H
#define GALAMENT_CLIENT_WORK_MODE_GET_STATISTIC_H

#include "abstract.h"

#include "websocket/client.h"
#include "common/protobuf/message_serializer.h"

namespace galament::client::work_mode {

class GetStatistic : public Abstract, websocket::EventsHandler {
public:
    GetStatistic(std::string_view address);

    void Run() override;

    void OnOpen(const websocket::Client::Connection& connection) override;
    void OnMessage(const websocket::Client::Connection& connection,
                   const std::string &payload) override;

private:
    websocket::Client client_;
    common::protobuf::MessageSerializer serializer_;
};

} // namespace galament::client::work_mode

#endif