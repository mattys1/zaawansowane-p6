#pragma once

struct MeasurementRecord {
	struct Date {
		int year;
		int month;
		int day;
	} date;

	double autoconsumption;
	double gridExport;
	double gridImport;
	double consumption;
	double production;

	bool operator==(const MeasurementRecord& other) const {
		return date.year == other.date.year &&
		       date.month == other.date.month &&
		       date.day == other.date.day &&
		       autoconsumption == other.autoconsumption &&
		       gridExport == other.gridExport &&
		       gridImport == other.gridImport &&
		       consumption == other.consumption &&
		       production == other.production;
	}
};
