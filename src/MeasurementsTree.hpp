#pragma once

#include <vector>
#include "Measurement.hpp"
#include "MeasurementRecord.hpp"

class MeasurementsTree {
private:
	std::vector<std::vector<std::vector<std::vector<std::vector<Measurement>>>>> tree;
public:
	using TreeType = decltype(tree);
	MeasurementsTree();

	void generate_measurement_tree(std::vector<MeasurementRecord> records);
	TreeType get_tree(void) const;
};
