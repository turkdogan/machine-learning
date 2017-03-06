#ifndef KNN_H
#define KNN_H
#include <vector>
#include <string>

#include "../common/ml_data.h"

class Knn
{
public:
	std::string getNeighbours(ClassificationData d, std::vector<ClassificationData> data_list, size_t k);
};

#endif