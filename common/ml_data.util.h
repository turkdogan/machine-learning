#ifndef ML_DATA_UTIL_H
#define ML_DATA_UTIL_H

#include <vector>
#include <algorithm>
#include <iostream>

#include "ml_data.h"

static double distance(const Data &d1, const Data &d2)
{
	double total = 0;
	for (size_t i = 0; i < d1.size; i++)
	{
		total += (std::pow(d1.fields[i] - d2.fields[i], 2));
	}
	return sqrt(total);
}

static void normalize(std::vector<Data> data)
{
	double max = std::numeric_limits<double>::max();
	double min = std::numeric_limits<double>::min();
	double *mins = new double[data[0].size];
	double *maxes = new double[data[0].size];
	std::fill_n(mins, data[0].size, max);
	std::fill_n(maxes, data[0].size, min);

	for (auto row : data) {
		for (size_t i = 0; i < row.size; i++) {
			if (row.fields[i] > maxes[i])
				maxes[i] = row.fields[i];
			if (row.fields[i] < mins[i])
				mins[i] = row.fields[i];
		}
	}
	for (auto row : data) {
		for (size_t i = 0; i < row.size; i++) {
			row.fields[i] = (row.fields[i] - mins[i]) / (maxes[i] - mins[i]);
		}
	}
}

static void printData(const std::vector<Data> data)
{
	for (auto d : data)
	{
		for (size_t i = 0; i < d.size; i++)
		{
			std::cout << d.fields[i] << " ";
		}
		std::cout << std::endl;
	}
}


#endif
