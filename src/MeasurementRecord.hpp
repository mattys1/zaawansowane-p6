#pragma once

struct MeasurementRecord {
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

	int operator<=>(const MeasurementRecord&) const = default;
};
