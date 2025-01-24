/**
* @file MeasurementsTree.cpp
* @brief Implementation of the MeasurementsTree class.
*/
#include "MeasurementsTree.hpp"

/**
* @brief Constructs an empty MeasurementsTree with pre-initialized structure.
*/
MeasurementsTree::MeasurementsTree(): tree {
		2, std::vector {
			12, std::vector {
				30, std::vector {
					4, std::vector<Measurement> {}
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
						4, std::vector<Measurement> {}
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
						4, std::vector<Measurement> {}
					});
				}
			}
		}
	}
}

/**
* @brief Generates a tree structure from a vector of measurement records.
*
* @param records The input measurement records to populate the tree.
*/
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

/**
* @brief Gets the underlying tree structure.
*
* @return TreeType The underlying tree structure.
*/
MeasurementsTree::TreeType MeasurementsTree::get_tree(void) const {
	return tree;
}

/**
* @brief Gets an iterator to the beginning of the tree.
*
* @return Iterator An iterator pointing to the beginning of the tree.
*/
MeasurementsTree::Iterator MeasurementsTree::begin() {
	return MeasurementsTree::Iterator(&tree, 0, 0, 0, 0, 0);
}

/**
* @brief Gets an iterator to the end of the tree.
*
* @return Iterator An iterator pointing to the end of the tree.
*/
MeasurementsTree::Iterator MeasurementsTree::end() {
	return Iterator(nullptr, tree.size());
}
