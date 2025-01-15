#include <gtest/gtest.h>
#include "MeasurementsImporter.hpp"
#include <print>

TEST(CsvImport, ReadTest) {
	MeasurementsImporter importer;

	importer.read_measurements("tests.csv");
}

/* TEST(CsvImport, CorrectReadTest) { */
/* 	std::array compare = { */
/* 		{ 01.10.2020 0:00,"0","0","406.8323","406.8323","0" }, */
/* 		{ 01.10.2020 0:15,"0","0","403.5656","403.5656","0" }, */
/* 		{ 01.10.2020 0:30,"0","0","336.7334","336.7334","0" }, */
/* 	} */
/* } */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
