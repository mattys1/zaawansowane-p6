#pragma once
#include "MeasurementRecord.hpp"
#include <string_view>
#include <vector>
#include <fstream>

class MeasurementsImporter {
public:
	std::vector<MeasurementRecord> read_measurements(const std::string_view fileName); 
};
