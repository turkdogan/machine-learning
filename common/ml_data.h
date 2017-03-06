#ifndef ML_DATA_H
#define ML_DATA_H

#include <string>

struct ClassificationData
{
	double *fields;
	size_t size;

	std::string clazz;

};

#endif