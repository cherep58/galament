#ifndef GALAMENT_COMMON_DATA_TYPES_TIMESTAMP_H
#define GALAMENT_COMMON_DATA_TYPES_TIMESTAMP_H

#include <chrono>

namespace galament::common::data_types {

using Timestamp = std::chrono::time_point<std::chrono::system_clock>;

Timestamp::rep ToUnixTimestamp(const Timestamp &timestamp);
Timestamp FromUnixTimestamp(Timestamp::rep unix_time);

} // galament::common::data_types

#endif
