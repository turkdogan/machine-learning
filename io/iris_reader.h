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
				d.clazz = segment;
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

#endif

