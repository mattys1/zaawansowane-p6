#include <gtest/gtest.h>
#include "MeasurementsImporter.hpp"
#include "MeasurementsTree.hpp"
#include "TreeManager.hpp"
#include <print>

TEST(CsvImport, ReadTest) {
	MeasurementsImporter importer;

	importer.read_measurements("empty.csv");
}

TEST(CsvImport, FullReadTest) {
	MeasurementsImporter importer;

	importer.read_measurements("Chart Export.csv");
}

TEST(CsvImport, CorrectConversionTest) {
	std::vector compare = {
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
		/* { 01.10.2020 0:00,"0","0","406.8323","406.8323","0" }, */
		/* { 01.10.2020 0:15,"0","0","403.5656","403.5656","0" }, */
		/* { 01.10.2020 0:30,"0","0","336.7334","336.7334","0" }, */
		/* { 01.10.2020 16:15,"119.3333","0","1871.7124","1991.0458","119.3333" } */
		/* { 31.10.2021 12:30,"416.3987","3064.2681","0","416.3987","3480.6667" }*/
	};

	MeasurementsImporter importer;
	importer.read_measurements("tests.csv");
	const auto measurements = importer.get_records();

	ASSERT_EQ(measurements, compare);
}

TEST(MeasurementsTree, ConversionTest) {
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

	std::vector compare {
        Measurement {
            .autoconsumption = 0.0,
            .gridExport = 0.0,
            .gridImport = 406.8323,
            .consumption = 406.8323,
            .production = 0.0,
            .timeMinutes = 0 // 0:00
        },
        Measurement {
            .autoconsumption = 0.0,
            .gridExport = 0.0,
            .gridImport = 403.5656,
            .consumption = 403.5656,
            .production = 0.0,
            .timeMinutes = 15 // 0:15
        },
        Measurement {
            .autoconsumption = 0.0,
            .gridExport = 0.0,
            .gridImport = 336.7334,
            .consumption = 336.7334,
            .production = 0.0,
            .timeMinutes = 30 // 0:30
        },
        Measurement {
            .autoconsumption = 119.3333,
            .gridExport = 0.0,
            .gridImport = 1871.7124,
            .consumption = 1991.0458,
            .production = 119.3333,
            .timeMinutes = 975 // 16:15
        },
        Measurement {
            .autoconsumption = 416.3987,
            .gridExport = 3064.2681,
            .gridImport = 0.0,
            .consumption = 416.3987,
            .production = 3480.6667,
            .timeMinutes = 750 // 12:30
        }
	};

	MeasurementsTree tree;
	tree.generate_measurement_tree(input);

	std::vector<Measurement> result;
	for(const auto& yearArr : tree.get_tree()) {
		for(const auto& monthArr : yearArr) {
			for(const auto& dayArr : monthArr) {
				for(const auto& quarter : dayArr) {
					for(const Measurement& measurement : quarter) {
						if(measurement != Measurement {}) {
							result.push_back(measurement);
						}
					}
				}
			}
		}
	}

	std::sort(result.begin(), result.end());
	std::sort(compare.begin(), compare.end());
	EXPECT_EQ(result, compare);
}

TEST(MeasurementsTree, IteratorTest) {
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

	std::vector<Measurement> compare;
	for(const auto& yearArr : tree.get_tree()) {
		for(const auto& monthArr : yearArr) {
			for(const auto& dayArr : monthArr) {
				for(const auto& quarter : dayArr) {
					for(const auto& measurement : quarter) {
						if(measurement != Measurement {}) {
							compare.push_back(measurement);
						}
					}
				}
			}
		}
	}

	std::vector<Measurement> result;

	for(auto iter { tree.begin() }; iter != tree.end(); ++iter) {
		result.push_back(*iter);
	}

	std::sort(result.begin(), result.end());
	std::sort(compare.begin(), compare.end());
	EXPECT_EQ(result, compare);
}

TEST(MeasurementsTree, AtTest) {
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

	auto begin { tree.begin() };
	auto end { tree.end() };
	auto test = tree.at(1, 9, 30, 2);
	auto testWalk = tree.at(1, 9, 30, 0);

	EXPECT_GT(tree.at(1, 9, 30, 2), begin);
	EXPECT_LE(tree.at(1, 9, 30, 2), end);
	EXPECT_NE(test, testWalk);
}

TEST(TreeManager, sumTest) {
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

	TreeManager manager(tree);

	const std::vector<Time> TimeInput {
		{
			.year = 2020,
			.month = 9,
			.day = 1,
			.inMinutes = 15, // 0:15
			.quarter = 1,
		},
		{
			.year = 2021,
			.month = 11,
			.day = 5,
			.inMinutes = 975,
			.quarter = 3
		}
	};

	double autoconsumptionResult { manager.autoconsumptionSum(TimeInput[0], TimeInput[1]) };
	double expected {};
	for(const auto& record : input) {
		expected += record.autoconsumption;
	}
	EXPECT_DOUBLE_EQ(autoconsumptionResult, expected);

	expected = 0;
	for(const auto& record : input) {
		expected += record.gridExport;
	}
	double exportResult = manager.exportSum(TimeInput[0], TimeInput[1]);
	EXPECT_DOUBLE_EQ(exportResult, expected);

	expected = 0;
	for(const auto& record : input) {
		expected += record.gridImport;
	}
	double importResult = manager.importSum(TimeInput[0], TimeInput[1]);
	EXPECT_DOUBLE_EQ(importResult, expected);

	expected = 0;
	for(const auto& record : input) {
		expected += record.consumption;
	}
	double consumptionResult = manager.consumptionSum(TimeInput[0], TimeInput[1]);
	EXPECT_DOUBLE_EQ(consumptionResult, expected);

	expected = 0;
	for(const auto& record : input) {
		expected += record.production;
	}
	double productionResult = manager.productionSum(TimeInput[0], TimeInput[1]);
	EXPECT_DOUBLE_EQ(productionResult, expected);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
