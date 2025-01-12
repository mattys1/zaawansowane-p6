#include "MeasurementTree.hpp"

MeasurementTree::MeasurementTree(): tree {
		std::vector {
			12, std::vector {
				30, std::vector {
					6, Measurement()
				}
			}
		},
	} {}
