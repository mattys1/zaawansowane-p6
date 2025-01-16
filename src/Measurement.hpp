#pragma once

#include <compare>
struct Measurement {
	double autoconsumption;
	double gridExport;
	double gridImport;
	double consumption;
	double production;
	int timeMinutes;

    auto operator<=>(const Measurement&) const = default;
};
