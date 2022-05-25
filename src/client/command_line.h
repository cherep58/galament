#ifndef GALAMENT_CLIENT_COMMAND_LINE_H
#define GALAMENT_CLIENT_COMMAND_LINE_H

#include <string_view>

namespace galament::client {

constexpr std::string_view kStatisticKey = "--statistic";
constexpr std::string_view kUsage = "Usage: host:port [--statistic]";

} // namespace galament::client::work_mode

#endif