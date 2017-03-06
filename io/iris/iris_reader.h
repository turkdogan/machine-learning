#ifndef IRIS_READER_H
#define IRIS_READER_H

#include "../../common/ml_data.h"
#include <vector>
#include <sstream>
#include <fstream>

static std::vector<ClassificationData> read_iris_data()
{
	const std::string path = "iris.data";
	std::vector<ClassificationData> data;
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
		ClassificationData d;
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

#endif

