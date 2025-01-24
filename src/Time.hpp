#pragma once

struct Time {
		int year;
		int month;
		int day;
		int inMinutes;
		int quarter;

		int operator<=>(const Time&) const = default;
};
