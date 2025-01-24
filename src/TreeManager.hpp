/**
* @file TreeManager.hpp
* @brief Defines the TreeManager class for managing and analyzing the MeasurementsTree.
*/
#pragma once

#include "MeasurementsTree.hpp"
#include "Time.hpp"

/**
* @brief Manages and analyzes data stored in a MeasurementsTree.
*/
class TreeManager {
private:
	MeasurementsTree tree;

	/**
	* @brief Private default constructor to prevent empty initialization.
	*/
	TreeManager() = default;
public:
	/**
	* @brief Constructs a TreeManager with the given MeasurementsTree.
	*
	* @param tree The MeasurementsTree to manage.
	*/
	TreeManager(MeasurementsTree tree): tree(tree) {};

	/**
	* @brief Calculates the sum of autoconsumption over a time range.
	*
	* @param start The start time of the range.
	* @param end The end time of the range.
	* @return double The sum of autoconsumption.
	*/
	double autoconsumptionSum(Time start, Time end);

	/**
	* @brief Calculates the sum of energy imported over a time range.
	*
	* @param start The start time of the range.
	* @param end The end time of the range.
	* @return double The sum of energy imported.
	*/
	double importSum(Time start, Time end);

	/**
	* @brief Calculates the sum of energy exported over a time range.
	*
	* @param start The start time of the range.
	* @param end The end time of the range.
	* @return double The sum of energy exported.
	*/
	double exportSum(Time start, Time end);

	/**
	* @brief Calculates the sum of energy consumed over a time range.
	*
	* @param start The start time of the range.
	* @param end The end time of the range.
	* @return double The sum of energy consumed.
	*/
	double consumptionSum(Time start, Time end);

	/**
	* @brief Calculates the sum of energy produced over a time range.
	*
	* @param start The start time of the range.
	* @param end The end time of the range.
	* @return double The sum of energy produced.
	*/
	double productionSum(Time start, Time end);
};
