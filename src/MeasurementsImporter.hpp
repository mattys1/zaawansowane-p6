#pragma once
#include "MeasurementRecord.hpp"
#include <string_view>
#include <vector>
#include <fstream>

class MeasurementsImporter {
private:
	std::vector<MeasurementRecord> records;
public:
	void read_measurements(const std::string_view fileName); 
	std::vector<MeasurementRecord> get_records() const;
};
