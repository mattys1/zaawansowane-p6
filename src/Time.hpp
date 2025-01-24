/**
* @file Time.hpp
* @brief Defines the Time struct for storing time-related data.
*/
#pragma once

/**
* @brief Represents a point in time for measurement purposes.
*/
struct Time {
		int year;
		int month;
		int day;
		int inMinutes;
		int quarter;

		int operator<=>(const Time&) const = default;
};
