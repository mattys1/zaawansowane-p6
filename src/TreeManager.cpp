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
