#include <gtest/gtest.h>
#include "MeasurementsImporter.hpp"
#include <print>

TEST(CsvImport, ReadTest) {
	MeasurementsImporter importer;

	importer.read_measurements("empty.csv");
}

TEST(CsvImport, CorrectConversionTest) {
	std::vector compare = {
		MeasurementRecord {
			.time = {
				.year = 2020,
				.month = 10,
				.day =  1,
				.quarter = 1
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
                .quarter = 1
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
                .quarter = 1
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
                .quarter = 3
            },
            .autoconsumption = 119.3333,
            .gridExport = 0.0,
            .gridImport = 1871.7124,
            .consumption = 1991.0458,
            .production = 119.3333
        }
		/* { 01.10.2020 0:00,"0","0","406.8323","406.8323","0" }, */
		/* { 01.10.2020 0:15,"0","0","403.5656","403.5656","0" }, */
		/* { 01.10.2020 0:30,"0","0","336.7334","336.7334","0" }, */
		/* { 01.10.2020 16:15,"119.3333","0","1871.7124","1991.0458","119.3333" } */
	};

	MeasurementsImporter importer;
	const auto measurements = importer.read_measurements("tests.csv");

	ASSERT_EQ(measurements, compare);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
