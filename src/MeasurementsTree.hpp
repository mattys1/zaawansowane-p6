#pragma once

#include <cassert>
#include <vector>
#include "Measurement.hpp"
#include "MeasurementRecord.hpp"

class MeasurementsTree {
private:
	std::vector<std::vector<std::vector<std::vector<std::vector<Measurement>>>>> tree;
public:
	using TreeType = decltype(tree);

	class Iterator {
	private:
		TreeType& tree;
		size_t year;
		size_t month;
		size_t day;
		size_t quarter;
		size_t measurement;

		void incrementSafe() {
			assert(year < tree.size());

			auto yearVec { tree[year] };
			auto monthVect { yearVec[month] };
			auto dayVec { monthVect[day] };
			auto quarterVec { dayVec[quarter] };
			auto record { quarterVec[measurement] };

			if(measurement >= quarterVec.size()) {
				measurement = 0;
				quarter++;
			}

			if(quarter >= dayVec.size()) {
				quarter = 0;
				day++;
			}

			if(quarter >= monthVect.size()) {
				day = 0;
				month++;
			}

			if(month >= yearVec.size()) {
				month = 0;
				year++;
			}

			assert(year < tree.size());
		}

		void decrementSafe() {
			auto yearVec { tree[year] };
			auto monthVec { yearVec[month] };
			auto dayVec { monthVec[day] };
			auto quarterVec { dayVec[quarter] };
			auto record { quarterVec[measurement] };

			if(measurement == 0) {
				measurement = quarterVec.size() - 1;
				quarter--;
			}

			if(quarter == 0) {
				quarter = dayVec.size() - 1;
				day--;
			}

			if(day == 0) {
				day = monthVec.size() - 1;
				month--;
			}

			if(month == 0) {
				month = yearVec.size() - 1;
				year--;
			}
		}
	public:
		Iterator(TreeType& tree, size_t year = 0, size_t month = 0, size_t day = 0, size_t quarter = 0, size_t measurement = 0):
			tree(tree),
			year(year),
			month(month),
			day(day),
			quarter(quarter),
			measurement(measurement) {}

		Measurement& operator*() {
			return tree[year][month][day][quarter][measurement];
		}

		std::strong_ordering operator<=>(const Iterator& other) const {
			if(year != other.year) {
				return year <=> other.year;
			} else if(month != other.month) {
				return month <=> other.month;
			} else if(day != other.day) {
				return day <=> other.day;
			} else if(quarter != other.quarter) {
				return quarter <=> other.quarter;
			} else {
				return measurement <=> other.measurement;
			}
		}	

		Iterator operator++() {
			incrementSafe();

			return Iterator(
				tree,
				year,
				month,
				day,
				quarter,
				measurement
			);
		}

		Iterator operator--() {
			decrementSafe();

			return Iterator(
				tree,
				year,
				month,
				day,
				quarter,
				measurement
			);
		}
	};
public:
	MeasurementsTree();

	void generate_measurement_tree(std::vector<MeasurementRecord> records);
	TreeType get_tree(void) const;
};
