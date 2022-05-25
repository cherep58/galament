#ifndef GALAMENT_COMMON_DATA_TYPES_UUID_H
#define GALAMENT_COMMON_DATA_TYPES_UUID_H

#include <array>
#include <string_view>

#include "boost/uuid/uuid.hpp"

namespace galament::common::data_types {

class Uuid {
public:
	Uuid() = default;
	Uuid(const boost::uuids::uuid &uuid);

	const boost::uuids::uuid& Get() const;

	bool FromBinaryString(std::string_view str);
	std::string ToString() const;

private:
	boost::uuids::uuid uuid_ = {};
};

} // galament::common::data_types

#endif
