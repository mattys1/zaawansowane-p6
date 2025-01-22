#include "MeasurementsTree.hpp"

MeasurementsTree::MeasurementsTree(): tree {
		2, std::vector {
			12, std::vector {
				30, std::vector {
					6, std::vector<Measurement> {}
				}
			}
		},
	} {
	for(size_t i = 0; i < tree.size(); i++) {
		auto& year = tree[i];
		const auto yearInCalendar { 2020 + i };

		for(size_t j = 0; j < year.size(); j++) {
			auto& month = year[j];
			const auto monthInCalendar = j + 1;

			if(monthInCalendar % 2 != 0) {
				if(monthInCalendar < 8) {
					month.push_back(std::vector {
						6, std::vector<Measurement> {}
					});
				}
			} else {
				if(monthInCalendar == 2) {
					if(yearInCalendar == 2020) {
						month.pop_back();
					} else { 
						month.pop_back();
						month.pop_back();
					}
				} else if(monthInCalendar >= 8) {
					month.push_back(std::vector {
						6, std::vector<Measurement> {}
					});
				}
			}
		}
	}
}

void MeasurementsTree::generate_measurement_tree(std::vector<MeasurementRecord> records) {
	for(const auto& record : records) {
		const auto time { record.time };

		auto& toFill { tree[time.year - 2020][time.month - 1][time.day - 1][time.quarter - 1] };

		toFill.push_back({ 
			.autoconsumption = record.autoconsumption ,
			.gridExport = record.gridExport     ,
			.gridImport = record.gridImport     ,
			.consumption = record.consumption   ,
			.production = record.production     ,
			.timeMinutes = record.time.inMinutes 
		});
	}
}
MeasurementsTree::TreeType MeasurementsTree::get_tree(void) const {
	return tree;
}
MeasurementsTree::Iterator MeasurementsTree::begin() {
	return MeasurementsTree::Iterator(tree, 0, 0, 0, 0, 0);
}

MeasurementsTree::Iterator MeasurementsTree::end() {
	return Iterator(tree, tree.size());
}
