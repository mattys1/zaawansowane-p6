#pragma once

struct MeasurementRecord {
	struct Time {
		int year;
		int month;
		int day;
		int quarter;
	} time;

	double autoconsumption;
	double gridExport;
	double gridImport;
	double consumption;
	double production;

	bool operator==(const MeasurementRecord& other) const {
		return time.year == other.time.year &&
		       time.month == other.time.month &&
		       time.day == other.time.day &&
			   time.quarter == other.time.quarter &&
		       autoconsumption == other.autoconsumption &&
		       gridExport == other.gridExport &&
		       gridImport == other.gridImport &&
		       consumption == other.consumption &&
		       production == other.production;
	}
};
