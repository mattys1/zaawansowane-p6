#include <print>
#include "MeasurementsTree.hpp"
#include "MeasurementsImporter.hpp"

int main (int argc, char *argv[]) {
	std::vector input = {
        MeasurementRecord {
            .time = {
                .year = 2020,
                .month = 10,
                .day = 1,
				.inMinutes = 0, // 0:00
                .quarter = 1,
            },
            .autoconsumption = 0.0,
            .gridExport = 0.0,
            .gridImport = 406.8323,
            .consumption = 406.8323,
            .production = 0.0
        },
        MeasurementRecord {
            .time = {
                .year = 2020,
                .month = 10,
                .day = 1,
				.inMinutes = 15, // 0:15
                .quarter = 1,
            },
            .autoconsumption = 0.0,
            .gridExport = 0.0,
            .gridImport = 403.5656,
            .consumption = 403.5656,
            .production = 0.0
        },
        MeasurementRecord {
            .time = {
                .year = 2020,
                .month = 10,
                .day = 1,
				.inMinutes = 30, // 0:30
                .quarter = 1,
            },
            .autoconsumption = 0.0,
            .gridExport = 0.0,
            .gridImport = 336.7334,
            .consumption = 336.7334,
            .production = 0.0
        },
        MeasurementRecord {
            .time = {
                .year = 2020,
                .month = 10,
                .day = 1,
				.inMinutes = 975, // 16:15
                .quarter = 3,
            },
            .autoconsumption = 119.3333,
            .gridExport = 0.0,
            .gridImport = 1871.7124,
            .consumption = 1991.0458,
            .production = 119.3333
        },
        MeasurementRecord {
            .time = {
                .year = 2021,
                .month = 10,
                .day = 31,
				.inMinutes = 750, // 12:30
                .quarter = 3,
            },
            .autoconsumption = 416.3987,
            .gridExport = 3064.2681,
            .gridImport = 0.0,
            .consumption = 416.3987,
            .production = 3480.6667
        }
	};

	MeasurementsTree tree;
	tree.generate_measurement_tree(input);

	std::vector<Measurement> result;

	for(const auto& measurement : tree) {
		result.push_back(measurement);
	}
}
