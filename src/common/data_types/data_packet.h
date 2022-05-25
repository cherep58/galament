#ifndef GALAMENT_COMMON_DATA_TYPES_DATA_PACKET_H
#define GALAMENT_COMMON_DATA_TYPES_DATA_PACKET_H

#include "uuid.h"
#include "timestamp.h"

namespace galament::common::data_types {

class DataPacket {
public:
	Uuid& uuid();
	const Uuid& uuid() const;

	Timestamp dt() const;
	void set_dt(const Timestamp &dt);

	float x() const;
	void set_x(float x);

	float y() const;
	void set_y(float y);

private:
	Uuid uuid_;
	Timestamp dt_;
	float x_ = 0.0;
	float y_ = 0.0;
};

} // galament::common::data_types

#endif
