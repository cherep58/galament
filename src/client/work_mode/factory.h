#ifndef GALAMENT_CLIENT_WORK_MODE_FACTORY_H
#define GALAMENT_CLIENT_WORK_MODE_FACTORY_H

#include "abstract.h"

#include <string_view>
#include <vector>
#include <memory>

namespace galament::client::work_mode {

class Factory {
public:
	static std::unique_ptr<Abstract> CreateFromCommandLine(const std::vector<std::string_view> &args);
};

} // namespace galament::client::work_mode

#endif