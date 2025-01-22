#include <print>
#include "MeasurementsTree.hpp"
#include "MeasurementsImporter.hpp"

int main (int argc, char *argv[]) {
	MeasurementsImporter importer;
	importer.read_measurements("tests.csv");

	MeasurementsTree tree;

	std::println("Hello world");

	/* for(const auto x : measurements) { */
	/* 	std::println(x); */
	/* } */
}
