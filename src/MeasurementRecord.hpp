/**
* @file MeasurementRecord.hpp
* @brief Defines the MeasurementRecord struct representing a detailed measurement record.
*/
#pragma once

#include <compare>

 /**
 * @brief Represents a detailed measurement record.
 */
struct MeasurementRecord {

	/**
	* @brief Nested Time struct to store time-related data.
	*/
	struct Time {
		int year;
		int month;
		int day;
		int inMinutes;
		int quarter;

		int operator<=>(const Time&) const = default;
	} time;

	double autoconsumption;
	double gridExport;
	double gridImport;
	double consumption;
	double production;

	std::partial_ordering operator<=>(const MeasurementRecord&) const = default;
};
