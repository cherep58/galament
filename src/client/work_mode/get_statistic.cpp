#include "get_statistic.h"

#include "helper/statistic_printer.h"

#include <thread>

namespace galament::client::work_mode {

using namespace galament::client::websocket;
using namespace galament::common::protobuf;
using namespace galament::common::message;

GetStatistic::GetStatistic(std::string_view address)
    : Abstract(address)
    , client_(*this)
{
	;
}

void GetStatistic::OnOpen(const Client::Connection& connection)
{
    connection.SendBinary(serializer_.SerializeWithoutPayload(MessageType::kStatisticRequest));
}

void GetStatistic::OnMessage(const Client::Connection& connection, const std::string& payload)
{
    helper::StatisticPrinter statistic_printer;
    serializer_.Unserialize(payload, statistic_printer);

    connection.Close();
}

void GetStatistic::Run()
{
    std::thread(&Client::Run, &client_, std::cref(address_)).join();
}

} // namespace galament::client::work_mode