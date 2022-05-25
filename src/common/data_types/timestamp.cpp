#include "timestamp.h"

namespace galament::common::data_types {

Timestamp::rep ToUnixTimestamp(const Timestamp &timestamp)
{
	return std::chrono::system_clock::to_time_t(timestamp);
}

Timestamp FromUnixTimestamp(Timestamp::rep unix_time)
{
	return std::chrono::system_clock::from_time_t(unix_time);
}

} // galament::common::data_types
