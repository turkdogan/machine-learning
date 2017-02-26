#include "knn.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "../io/iris_reader.h"

void run_knn(std::vector<Data> test, std::vector<Data> training, size_t k)
{
	Knn knn;
	size_t correct = 0; 
	for (auto test_data : test)
	{
		std::string maxClass = knn.getNeighbours(test_data, training, k);
		if (maxClass.compare(test_data.cls) == 0)
		{
			correct++;
		}
	}
	std::cout << 
		correct << " of "<< test.size() << 
		" (" << 
		static_cast<double>(100.0) *correct/static_cast<double>(test.size()) <<
		")" << std::endl;
	
}


int main(int argc, char **argv)
{
	std::srand(time(NULL));
	auto dataset = read_iris_data();
	printData(dataset);
	normalize(dataset);
	std::random_shuffle(dataset.begin(), dataset.end());
	auto splitted_data = split_data(dataset);
	dataset.clear();
	run_knn(splitted_data.second, splitted_data.first, 10);
	system("pause");
	return 0;
}