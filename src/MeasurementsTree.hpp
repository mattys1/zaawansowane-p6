/**
* @file MeasurementsTree.hpp
* @brief Defines the MeasurementsTree class for managing measurement data in a tree structure.
*/
#pragma once

#include <cassert>
#include <span>
#include <vector>
#include "Measurement.hpp"
#include "MeasurementRecord.hpp"

using TreeType = std::vector<std::vector<std::vector<std::vector<std::vector<Measurement>>>>>;

/**
* @brief Manages measurement data in a hierarchical tree structure.
*/
class MeasurementsTree {
private:
	using TreeType = std::vector<std::vector<std::vector<std::vector<std::vector<Measurement>>>>>;
	TreeType tree;

	constexpr static TreeType endDummy { TreeType {} };
public:
	/**
		* @brief Nested iterator class for traversing the MeasurementsTree.
	*/
	class Iterator {
	private:
		TreeType* tree;
		size_t yearIdx;
		size_t monthIdx;
		size_t dayIdx;
		size_t quarterIdx;
		size_t measurementIdx;

		/**
		* @brief Safely increments the iterator.
		*
		* @return int Returns -1 if the end is reached; otherwise, 0.
		*/
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

		/**
		* @brief Moves the iterator to the next valid position.
		*/
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

		/**
		* @brief Safely decrements the iterator.
		*/
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
		/**
		* @brief Constructs an iterator for the MeasurementsTree.
		*
		* @param _tree Pointer to the tree structure.
		* @param year Year index (default 0).
		* @param month Month index (default 0).
		* @param day Day index (default 0).
		* @param quarter Quarter index (default 0).
		* @param measurement Measurement index (default 0).
		* @param walkToCorrect Flag to walk to the next valid position (default true).
		*/
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

		/**
		* @brief Dereferences the iterator to access the current measurement.
		*
		* @return Measurement& Reference to the current measurement.
		*/
		Measurement& operator*() {
			auto measurements { (*tree)[yearIdx][monthIdx][dayIdx][quarterIdx] };

			assert(!measurements.empty());

			return (*tree)[yearIdx][monthIdx][dayIdx][quarterIdx][measurementIdx];
		}

		/**
		* @brief Compares two iterators for strong ordering.
		*
		* @param other Another iterator to compare.
		* @return std::strong_ordering Comparison result.
		*/
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

		/**
		* @brief Checks if two iterators are not equal.
		*
		* @param other Another iterator to compare.
		* @return bool True if iterators are not equal; otherwise, false.
		*/
		bool operator!=(const Iterator& other) const {
			return (*this <=> other) != std::strong_ordering::equal;
		}	

		/**
		* @brief Pre-increments the iterator to the next position.
		*
		* @return Iterator& Reference to the updated iterator.
		*/
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

		/**
		* @brief Pre-decrements the iterator to the previous position.
		*
		* @return Iterator& Reference to the updated iterator.
		*/
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
	/**
	* @brief Constructs a new MeasurementsTree object.
	*/
	MeasurementsTree();

	/**
	* @brief Gets an iterator to the beginning of the tree.
	*
	* @return Iterator An iterator pointing to the beginning of the tree.
	*/
	Iterator begin(); 

	/**
	* @brief Gets an iterator to the end of the tree.
	*
	* @return Iterator An iterator pointing to the end of the tree.
	*/
	Iterator end(); 
	Iterator at(
		const size_t year = 0,
		const size_t month = 0,
		const size_t day = 0,
		const size_t quarter = 0,
		const size_t measurement = 0,
		const bool walkToCorrect = false
	);

	/**
	* @brief Populates the tree with measurement records.
	*
	* @param records Vector of measurement records to populate the tree.
	*/
	void generate_measurement_tree(std::vector<MeasurementRecord> records);

	/**
	* @brief Retrieves the underlying tree structure.
	*
	* @return TreeType The underlying tree structure.
	*/
	TreeType get_tree(void) const;
};
