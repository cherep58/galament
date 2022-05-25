#ifndef GALAMENT_COMMON_DATA_TYPES_UUID_STATISTIC_H
#define GALAMENT_COMMON_DATA_TYPES_UUID_STATISTIC_H

#include "uuid.h"

namespace galament::common::data_types {

class UuidStatistic {
public:

	Uuid& uuid();
	const Uuid& uuid() const;

	float x_1min() const;
	void set_x_1min(float x_1min);

	float y_1min() const;
	void set_y_1min(float y_1min);

	float x_5min() const;
	void set_x_5min(float x_5min);

	float y_5min() const;
	void set_y_5min(float y_5min);

private:
	Uuid uuid_;
	float x_1min_ = 0.0;
	float y_1min_ = 0.0;
	float x_5min_ = 0.0;
	float y_5min_ = 0.0;
};

} // galament::common::data_types

#endif
