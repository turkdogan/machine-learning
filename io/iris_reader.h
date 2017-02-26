#ifndef IRIS_READER_H
#define IRIS_READER_H

#include "../common/ml_data.h"
#include <vector>
#include <sstream>
#include <fstream>

static std::vector<Data> read_iris_data()
{
	const std::string path = "data/iris.data";
	std::vector<Data> data;
	std::ifstream input(path);
	std::string line;
	while(std::getline(input, line))
	{
		if (line.empty())
		{
			continue;
		}

		std::stringstream test(line);
		std::string segment;
		std::vector<std::string> seglist;

		double *fields = new double[10];
		Data d;
		d.fields = fields;
		d.size = 4;
		int index = 0;
		while (std::getline(test, segment, ','))
		{
			if (index == d.size)
			{
				d.cls = segment;
				break;
			}

			fields[index] = std::stod(segment);
			index++;
		}
		data.push_back(d);
	}
	return data;
}

static std::pair<std::vector<Data>, std::vector<Data>> split_data(std::vector<Data> data)
{
	std::vector<Data> training;
	std::vector<Data> test;
	size_t percentage70 = data.size() * 0.7;
	size_t index = 0;
	while (index < percentage70)
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

