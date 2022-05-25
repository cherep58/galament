#include "statistic_printer.h"

#include "boost/format.hpp"

#include <iostream>
#include <iomanip>

namespace galament::helper {

using namespace galament::common::data_types;

void StatisticPrinter::Visit(const Statistic& statistic)
{
	PrintHeader();

	for (const auto& s : statistic) {
		PrintUuidStatistic(s);
		PrintDelimiter();
	}
}

void StatisticPrinter::PrintHeader() const
{
	PrintDelimiter();
	std::cout 
		<< boost::format("| %36s | %10s | %10s | %10s | %10s |") % "UUID" % "X_1" % "Y_1" % "X_5" % "Y_5" 
		<< std::endl;
	PrintDelimiter();
}

void StatisticPrinter::PrintDelimiter() const
{
	std::cout 
		<< boost::format("%s") % boost::io::group(std::setw(92), std::setfill('-'), "") 
		<< std::endl;
}

void StatisticPrinter::PrintUuidStatistic(const UuidStatistic& statistic) const
{
	auto format = boost::format("| %36s | %10.2f | %10.2f | %10.2f | %10.2f |")
		% statistic.uuid().ToString()
		% statistic.x_1min()
		% statistic.y_1min()
		% statistic.x_5min()
		% statistic.y_5min();

	std::cout << format << std::endl;
}

} // namespace galament::helper