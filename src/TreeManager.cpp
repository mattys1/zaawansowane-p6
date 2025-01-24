#include "TreeManager.hpp"

double TreeManager::autoconsumptionSum(Time start, Time end) {
	const auto adjustTime {[](Time& time) {
		time.day--;
		time.month--;
		time.quarter--;
		time.year -= 2020;
	}};

	adjustTime(start);
	adjustTime(end);

	auto beginQuarter { tree.at(start.year, start.month, start.day, start.quarter, true) };
	auto endQuarter { tree.at(end.year, end.month, end.day, end.quarter, false) };

	double autoconsumptionSum {};

	for(; beginQuarter <= endQuarter; ++beginQuarter) {
		const auto val { *beginQuarter };
		autoconsumptionSum += val.autoconsumption;
	}

	return autoconsumptionSum;
}
