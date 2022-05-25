#include "uuid_statistic.h"

namespace galament::common::data_types {

Uuid& UuidStatistic::uuid()
{
	return uuid_;
}

const Uuid& UuidStatistic::uuid() const
{
	return uuid_;
}

float UuidStatistic::x_1min() const
{
	return x_1min_;
}

void UuidStatistic::set_x_1min(float x_1min)
{
	x_1min_ = x_1min;
}

float UuidStatistic::y_1min() const
{
	return y_1min_;
}

void UuidStatistic::set_y_1min(float y_1min)
{
	y_1min_ = y_1min;
}

float UuidStatistic::x_5min() const
{
	return x_5min_;
}

void UuidStatistic::set_x_5min(float x_5min)
{
	x_5min_ = x_5min;
}

float UuidStatistic::y_5min() const
{
	return y_5min_;
}

void UuidStatistic::set_y_5min(float y_5min)
{
	y_5min_ = y_5min;
}

} // galament::common::data_types
