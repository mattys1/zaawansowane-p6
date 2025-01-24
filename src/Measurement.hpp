/**
 * @file Measurement.hpp
 * @brief Defines the Measurement struct representing a single measurement.
 */
#pragma once

#include <compare>

 /**
  * @brief Represents a single measurement.
  */
struct Measurement {
	double autoconsumption;
	double gridExport;
	double gridImport;
	double consumption;
	double production;
	int timeMinutes;

    auto operator<=>(const Measurement&) const = default;
};
