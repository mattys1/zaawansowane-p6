/**
* @file TreeManager.cpp
* @brief Implementation of the TreeManager class for analyzing MeasurementsTree data.
*/

#include "TreeManager.hpp"

/**
* @brief Calculates the sum of autoconsumption over a time range.
*
* @param start The start time of the range.
* @param end The end time of the range.
* @return double The sum of autoconsumption.
*/
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

/**
* @brief Calculates the sum of energy imported over a time range.
*
* @param start The start time of the range.
* @param end The end time of the range.
* @return double The sum of energy imported.
*/
double TreeManager::importSum(Time start, Time end) {
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

	double importSum {};

	for(; beginQuarter <= endQuarter; ++beginQuarter) {
		const auto val { *beginQuarter };
		importSum += val.gridImport;
	}

	return importSum;
}

/**
* @brief Calculates the sum of energy exported over a time range.
*
* @param start The start time of the range.
* @param end The end time of the range.
* @return double The sum of energy exported.
*/
double TreeManager::exportSum(Time start, Time end) {
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

	double exportSum {};

	for(; beginQuarter <= endQuarter; ++beginQuarter) {
		const auto val { *beginQuarter };
		exportSum += val.gridExport;
	}

	return exportSum;
}

/**
* @brief Calculates the sum of energy consumed over a time range.
*
* @param start The start time of the range.
* @param end The end time of the range.
* @return double The sum of energy consumed.
*/
double TreeManager::consumptionSum(Time start, Time end) {
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

	double consumptionSum {};

	for(; beginQuarter <= endQuarter; ++beginQuarter) {
		const auto val { *beginQuarter };
		consumptionSum += val.consumption;
	}

	return consumptionSum;
}

/**
* @brief Calculates the sum of energy produced over a time range.
*
* @param start The start time of the range.
* @param end The end time of the range.
* @return double The sum of energy produced.
*/
double TreeManager::productionSum(Time start, Time end) {
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

	double productionSum {};

	for(; beginQuarter <= endQuarter; ++beginQuarter) {
		const auto val { *beginQuarter };
		productionSum += val.production;
	}

	return productionSum;
}
