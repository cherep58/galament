#include "uuid.h"

#include "boost/uuid/uuid_io.hpp"

namespace galament::common::data_types {

Uuid::Uuid(const boost::uuids::uuid& uuid)
	: uuid_(uuid)
{
	;
}

const boost::uuids::uuid& Uuid::Get() const
{
	return uuid_;
}

bool Uuid::FromBinaryString(std::string_view str)
{
	if (str.length() != uuid_.size()) {
		return false;
	}

	std::copy(str.begin(), str.end(), uuid_.begin());
	return true;
}

std::string Uuid::ToString() const
{
	return boost::uuids::to_string(uuid_);
}

} // galament::common::data_types