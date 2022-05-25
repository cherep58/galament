#ifndef GALAMENT_COMMON_MESSAGE_MESSAGE_VISITOR_H
#define GALAMENT_COMMON_MESSAGE_MESSAGE_VISITOR_H

#include "common/data_types/data_packet.h"
#include "common/data_types/statistic.h"

namespace galament::common::message {

class MessageVisitor {
public:
	virtual void Visit(const data_types::DataPacket&) {};
	virtual void Visit(const data_types::Statistic&) {};
	virtual void VisitStatisticRequest() {};
};

} // galament::common::message

#endif
