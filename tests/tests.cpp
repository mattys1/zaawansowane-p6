#include <gtest/gtest.h>
#include "MeasurementsImporter.hpp"
#include <print>

TEST(CsvImport, ReadTest) {
	std::println("ReadTest");
	MeasurementsImporter importer;
	std::vector<MeasurementRecord> records;

	EXPECT_EQ(importer.read_measurements("Chart Export.csv"), std::vector<MeasurementRecord>());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
