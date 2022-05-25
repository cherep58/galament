#include "data_packet.h"

namespace galament::common::data_types {

Uuid& DataPacket::uuid()
{
	return uuid_;
}

const Uuid& DataPacket::uuid() const
{
	return uuid_;
}

Timestamp DataPacket::dt() const
{
	return dt_;
}

void DataPacket::set_dt(const Timestamp &dt)
{
	dt_ = dt;
}

float DataPacket::x() const
{
	return x_;
}

void DataPacket::set_x(float x)
{
	x_ = x;
}

float DataPacket::y() const
{
	return y_;
}

void DataPacket::set_y(float y)
{
	y_ = y;
}

} // galament::common::data_types
