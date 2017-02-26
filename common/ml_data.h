#ifndef ML_DATA_H
#define ML_DATA_H

#include <string>

struct Data
{
	double *fields;
	size_t size;

	std::string clazz;

};

#endif