#include "MeasurementsImporter.hpp"
#include <algorithm>
#include <cassert>
#include <print>
#include <ranges>

std::vector<MeasurementRecord> MeasurementsImporter::read_measurements(const std::string_view fileName) {
	std::fstream measurementsFile;
	measurementsFile.open(fileName.data(), std::fstream::in);
 
	if(!measurementsFile.is_open()) {
		throw std::runtime_error("Could not open file");
	}

	std::vector<std::string> lines;
	std::string line; 
	while(std::getline(measurementsFile, line)) {
		if(line.empty() || std::find_if(line.begin(), line.end(), [](const auto ch) { return !isspace(ch); }) == line.end()) {
			continue;
		};

		lines.emplace_back(line);
	}

	if(lines.size() == 0) {
		return {};
	}

	std::span dataLines { lines.begin() + 1, lines.end() };

	std::vector<MeasurementRecord> records;
	records.reserve(dataLines.size());
	for(const auto& line : dataLines) {
		auto entries { std::views::split(line, ',') | std::ranges::to<std::vector<std::string>>() };
		assert(entries.size() == 6);	

		const auto DateAndHourTime { entries[0] |
			std::views::split(' ') |
			std::ranges::to<std::vector<std::string>>() };

		const auto& date { DateAndHourTime[0] }, hourTime { DateAndHourTime[1] };

		const auto splitDate { date |
			std::views::split('.') |
			std::ranges::to<std::vector<std::string>>() };

		const auto& day { splitDate[0] }, month { splitDate[1] }, year { splitDate[2] };
		
		for(auto& x : entries) {
			x.erase(remove(x.begin(), x.end(), '\"'), x.end());
		}

		try {
			std::println();
			records.push_back(
				MeasurementRecord {
					.time = {
						.year = std::stoi(year),
						.month = std::stoi(month),
						.day =  std::stoi(day),
						.quarter = [](const std::string_view hourTime) -> int {
							const auto minutesPerQuarter { 24 * 60 / 4 };

							const auto hoursMinutes { hourTime |
								std::views::split(':') |
								std::ranges::to<std::vector<std::string>>()
								/* std::ranges::to<std::vector<std::string>>() }; */
							};

							const auto timeInMinutes { std::stoi(hoursMinutes[0]) * 60 + std::stoi(hoursMinutes[1]) };

							return timeInMinutes / minutesPerQuarter + 1;
						}(hourTime)
					},

					.autoconsumption = std::stod(entries[1]),
					.gridExport = std::stod(entries[2]),
					.gridImport = std::stod(entries[3]),
					.consumption = std::stod(entries[4]),
					.production = std::stod(entries[5])
				}
			);
		} catch(std::exception& e) {
			std::print("Error: {}\n", e.what());

		}
	}

	return records;
}
