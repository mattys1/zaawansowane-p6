#pragma once

#include "MeasurementsTree.hpp"
#include "Time.hpp"

class TreeManager {
private:
	MeasurementsTree tree;
	TreeManager() = default;
public:
	TreeManager(MeasurementsTree tree): tree(tree) {};

	double autoconsumptionSum(Time start, Time end);
	double importSum(Time start, Time end);
	double exportSum(Time start, Time end);
	double consumptionSum(Time start, Time end);
	double productionSum(Time start, Time end);
};
