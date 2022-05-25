#include "factory.h"
#include "command_line.h"
#include "get_statistic.h"
#include "send_data_packet.h"

namespace galament::client::work_mode {

std::unique_ptr<Abstract> Factory::CreateFromCommandLine(const std::vector<std::string_view>& args)
{
	if (args.empty()) {
		return nullptr;
	}

	const auto& uri = args[0];

	if (args.size() > 1) {
		if (args[1] == kStatisticKey) {
			return std::make_unique<GetStatistic>(uri);
		}
	}

	return std::make_unique<SendDataPacket>(uri);
}

} // namespace galament::client::work_mode