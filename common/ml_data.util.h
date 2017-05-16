#ifndef ML_DATA_UTIL_H
#define ML_DATA_UTIL_H

#include <vector>
#include <algorithm>
#include <iostream>

#include "ml_data.h"

static double distance(const Item &d1, const Item &d2)
{
	double total = 0;
	for (size_t i = 0; i < d1.size; i++)
	{
		total += (std::pow(d1.fields[i] - d2.fields[i], 2));
	}
	return sqrt(total);
}

static void normalize(std::vector<Item> data)
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

static void printData(const std::vector<Item> data)
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

static std::pair<std::vector<Item>, std::vector<Item>> split_data(
	std::vector<Item> data, double percentage)
{
	std::vector<Item> training;
	std::vector<Item> test;
	size_t percentage_count = data.size() * percentage;
	size_t index = 0;
	while (index < percentage_count)
	{
		training.push_back(data[index]);
		index++;
	}
	while (index < data.size())
	{
		test.push_back(data[index]);
		index++;
	}
	return std::make_pair(training, test);
}


#endif
