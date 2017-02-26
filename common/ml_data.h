#ifndef ML_DATA_H
#define ML_DATA_H

#include <string>
#include <algorithm>

struct Data
{
	double *fields;
	size_t size;

	std::string cls;

	double distance(Data d) const
	{
		double total = 0;
		for (size_t i = 0; i < d.size; i++)
		{
			total += (std::pow(d.fields[i] - fields[i], 2));
		}
		return sqrt(total);
	}
};

#endif