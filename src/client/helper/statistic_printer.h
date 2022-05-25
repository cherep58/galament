#ifndef GALAMENT_CLIENT_HELPER_STATISTIC_PRINTER_H
#define GALAMENT_CLIENT_HELPER_STATISTIC_PRINTER_H

#include "common/message/message_visitor.h"

namespace galament::helper {

class StatisticPrinter : public common::message::MessageVisitor {
public:
	void Visit(const common::data_types::Statistic& statistic);

private:
	void PrintHeader() const;
	void PrintDelimiter() const;
	void PrintUuidStatistic(const common::data_types::UuidStatistic& statistic) const;
};

} // namespace galament::helper

#endif