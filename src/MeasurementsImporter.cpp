#include "MeasurementsImporter.hpp"
#include <print>

std::vector<MeasurementRecord> MeasurementsImporter::read_measurements(const std::string_view fileName) {
	std::fstream measurementsFile;
	measurementsFile.open(fileName.data(), std::fstream::in);
 
	if(!measurementsFile.is_open()) {
		throw std::runtime_error("Could not open file");
	}

	std::string line; 
	while(std::getline(measurementsFile, line)) {
		if(line.empty()) {
			continue;
		}

		std::println("Line: {}", line);
	}

	return {};
}
