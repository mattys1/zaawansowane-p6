#pragma once

#include <cassert>
#include <span>
#include <vector>
#include "Measurement.hpp"
#include "MeasurementRecord.hpp"

using TreeType = std::vector<std::vector<std::vector<std::vector<std::vector<Measurement>>>>>;

class MeasurementsTree {
private:
	using TreeType = std::vector<std::vector<std::vector<std::vector<std::vector<Measurement>>>>>;
	TreeType tree;

	constexpr static TreeType endDummy { TreeType {} };
public:
	class Iterator {
	private:
		TreeType* tree;
		size_t yearIdx;
		size_t monthIdx;
		size_t dayIdx;
		size_t quarterIdx;
		size_t measurementIdx;


		int incrementSafe() {
			assert(monthIdx < (*tree)[yearIdx].size());
			assert(dayIdx < (*tree)[yearIdx][monthIdx].size());
			assert(quarterIdx < (*tree)[yearIdx][monthIdx][dayIdx].size());
			/* assert(measurementIdx < (*tree)[yearIdx][monthIdx][dayIdx][quarterIdx].size()); */

			auto& yearVec { (*tree)[yearIdx] };
			auto& monthVect { yearVec[monthIdx] };
			auto& dayVec { monthVect[dayIdx] };
			auto& quarterVec { dayVec[quarterIdx] };

			/* assert(quarterVec.empty()); */
			measurementIdx++;
			if (measurementIdx >= quarterVec.size()) {
				measurementIdx = 0;
				quarterIdx++;

				if (quarterIdx >= dayVec.size()) {
					quarterIdx = 0;
					dayIdx++;

					if (dayIdx >= monthVect.size()) {
						dayIdx = 0;
						monthIdx++;

						if (monthIdx >= yearVec.size()) {
							monthIdx = 0;
							yearIdx++;

							if (yearIdx >= tree->size()) {
								return -1;
							}
						}
					}
				}
    }
			/* Measurement& measurement { quarterVec[measurementIdx] }; */
			return 0;
		}

		void goToNextValid() {
			//FIXME: get the reference to the actual member vectors not the copies
			std::span yearVec { (*tree)[yearIdx] };
			std::span monthVec { yearVec[monthIdx] };
			std::span dayVec { monthVec[dayIdx] };
			std::span quarterVec { dayVec[quarterIdx] };

			while(quarterVec.empty() && yearIdx < tree->size()) {
				const auto end { incrementSafe() };

				if(end < 0) {
					break;	
				}

				yearVec = (*tree)[yearIdx];            
				monthVec = yearVec[monthIdx];       
				dayVec = monthVec[dayIdx];
				quarterVec = dayVec[quarterIdx];    			
			}

		}
		void decrementSafe() {
			std::span yearVec { tree[yearIdx] };
			std::span monthVec { yearVec[monthIdx] };
			std::span dayVec { monthVec[dayIdx] };
			std::span quarterVec { dayVec[quarterIdx] };
			std::span record { quarterVec[measurementIdx] };

			if(measurementIdx == 0) {
				measurementIdx = quarterVec.size() - 1;
				quarterIdx--;
			}

			if(quarterIdx == 0) {
				quarterIdx = dayVec.size() - 1;
				dayIdx--;
			}

			if(dayIdx == 0) {
				dayIdx = monthVec.size() - 1;
				monthIdx--;
			}

			if(monthIdx == 0) {
				monthIdx = yearVec.size() - 1;
				yearIdx--;
			}
		}
	public:
		Iterator(TreeType* _tree, size_t year = 0, size_t month = 0, size_t day = 0, size_t quarter = 0, size_t measurement = 0, bool walkToCorrect = true):
			tree(_tree),
			yearIdx(year),
			monthIdx(month),
			dayIdx(day),
			quarterIdx(quarter),
			measurementIdx(measurement) {
			if(tree != nullptr && walkToCorrect == true) {
				goToNextValid();
			}
		}

		Measurement& operator*() {
			auto measurements { (*tree)[yearIdx][monthIdx][dayIdx][quarterIdx] };

			assert(!measurements.empty());

			return (*tree)[yearIdx][monthIdx][dayIdx][quarterIdx][measurementIdx];
		}

		std::strong_ordering operator<=>(const Iterator& other) const {
			if(yearIdx == tree->size() && yearIdx == other.yearIdx) { // for end iterator
				return std::strong_ordering::equal;
			}

			if(yearIdx != other.yearIdx) {
				return yearIdx <=> other.yearIdx;
			} else if(monthIdx != other.monthIdx) {
				return monthIdx <=> other.monthIdx;
			} else if(dayIdx != other.dayIdx) {
				return dayIdx <=> other.dayIdx;
			} else if(quarterIdx != other.quarterIdx) {
				return quarterIdx <=> other.quarterIdx;
			} else {
				return measurementIdx <=> other.measurementIdx;
			} 

			return std::strong_ordering::equal;
		}	

		bool operator!=(const Iterator& other) const {
			return (*this <=> other) != std::strong_ordering::equal;
		}	

		bool operator==(const Iterator& other) const {
			return !operator!=(other);
		}

		Iterator operator++() {
			incrementSafe();
			goToNextValid();

			if(yearIdx >= tree->size()) {
				return Iterator(nullptr, tree->size());
			}

			return(*this);
		}

		Iterator operator--() {
			decrementSafe();

			return Iterator(
				tree,
				yearIdx,
				monthIdx,
				dayIdx,
				quarterIdx,
				measurementIdx
			);
		}
	};

public:
	MeasurementsTree();

	Iterator begin(); 
	Iterator end(); 
	Iterator at(
		const size_t year = 0,
		const size_t month = 0,
		const size_t day = 0,
		const size_t quarter = 0,
		const size_t measurement = 0,
		const bool walkToCorrect = false
	);

	void generate_measurement_tree(std::vector<MeasurementRecord> records);
	TreeType get_tree(void) const;
};
