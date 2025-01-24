/**
* @file MeasurementsImporter.hpp
* @brief Defines the MeasurementsImporter class for reading measurement data.
*/
#pragma once
#include "MeasurementRecord.hpp"
#include <string_view>
#include <vector>
#include <fstream>

/**
* @brief Handles importing and reading measurement records from files.
*/
class MeasurementsImporter {
private:
	std::vector<MeasurementRecord> records;
public:
	/**
	* @brief Reads measurement records from the specified file.
	*
	* @param fileName The name of the file to read measurements from.
	*/
	void read_measurements(const std::string_view fileName); 

	/**
	* @brief Retrieves the imported measurement records.
	*
	* @return std::vector<MeasurementRecord> A vector of measurement records.
	*/
	std::vector<MeasurementRecord> get_records() const;
};
