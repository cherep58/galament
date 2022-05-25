#include "abstract.h"

namespace galament::client::work_mode {

Abstract::Abstract(std::string_view address)
	: address_(address)
{
	;
}

} // namespace galament::client::work_mode