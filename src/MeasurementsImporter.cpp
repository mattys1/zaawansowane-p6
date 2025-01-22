#include "MeasurementsImporter.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <ranges>

void MeasurementsImporter::read_measurements(const std::string_view fileName) {
	const auto check_for_double { [this](const MeasurementRecord& record) -> bool {
		return std::ranges::find(records, record) != records.end();
	}};

	const auto log { [](std::string_view line, std::fstream& file) {
		const auto time { std::chrono::system_clock::now() };

		file << std::format("{}: Loading record: {}\n", time, line);
	}};

	const auto log_err { [](std::string_view line, const std::string_view message, std::fstream& file) {
		const auto time { std::chrono::system_clock::now() };

		file << std::format("{}: {}: {}\n", time, message, line);
	}};

	std::fstream measurementsFile;
	measurementsFile.open(fileName.data(), std::fstream::in);
 
	if(!measurementsFile.is_open()) {
		throw std::runtime_error("Could not open input file");
	}

	std::fstream errorLogs; errorLogs.open("log_error_data_godzina.txt", std::fstream::app);
	if(!errorLogs.is_open()) {
		throw std::runtime_error("Could not open error log file");
	}

	std::fstream allLogs; allLogs.open("log_data_godzina.txt", std::fstream::app);
	if(!allLogs.is_open()) {
		throw std::runtime_error("Could not open log file");
	}

	std::vector<std::string> lines;
	std::string line; 
	while(std::getline(measurementsFile, line)) {
		if(line.empty() || std::find_if(line.begin(), line.end(), [](const auto ch) { return !isspace(ch); }) == line.end()) {
			continue;
		};

		log(line, allLogs);

		if(const auto invalid = std::find_if(line.begin(), line.end(), [](const auto x) {
			return !((x >= '0' && x <= '9') || x == '.' || x == ',' || x == ':' || x == '\"' || isspace(x));
		}); invalid != line.end()) {
			log_err(line, "Line with invalid characters", errorLogs);
			continue;
		}

		lines.emplace_back(line);
	}

	if(lines.size() == 0) {
		return;
	}

	records.reserve(lines.size());
	for(const auto& line : lines) {
		auto entries { std::views::split(line, ',') | std::ranges::to<std::vector<std::string>>() };

		if(entries.size() != 6) {
			log_err(line, "Invalid entry size", errorLogs);
			continue;
		}

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

		const auto minutesPerQuarter { 24 * 60 / 4 };

		const auto hoursMinutes { hourTime |
			std::views::split(':') |
			std::ranges::to<std::vector<std::string>>()
			/* std::ranges::to<std::vector<std::string>>() }; */
		};

		const auto timeInMinutes { std::stoi(hoursMinutes[0]) * 60 + std::stoi(hoursMinutes[1]) };

		/* return timeInMinutes / minutesPerQuarter + 1; */

		const auto record { [&]() -> std::variant<MeasurementRecord, std::exception> const {
			try {
				return MeasurementRecord {
					.time = {
						.year = std::stoi(year),
						.month = std::stoi(month),
						.day =  std::stoi(day),
						.inMinutes = timeInMinutes,
						.quarter = 	timeInMinutes / minutesPerQuarter + 1				
					},

					.autoconsumption = std::stod(entries[1]),
					.gridExport = std::stod(entries[2]),
					.gridImport = std::stod(entries[3]),
					.consumption = std::stod(entries[4]),
					.production = std::stod(entries[5])
				};
			} catch(std::exception& e) {
				return e;
			}
		}()};

		if(std::holds_alternative<std::exception>(record)) {
			log_err(line, "Error converting line to values", errorLogs);
			continue;
		}

		if(check_for_double(std::get<MeasurementRecord>(record))) {
			log_err(line, "Line already exists", errorLogs);
			continue;
		}

		records.push_back(std::get<MeasurementRecord>(record));
	}
}

std::vector<MeasurementRecord> MeasurementsImporter::get_records() const {
	return records;
}
