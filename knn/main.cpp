#include "knn.h"
#include <iostream>
#include <ctime>

#include "../io/iris/iris_reader.h"
#include "../io/ddm/breast_cancer_reader.h"
#include "../common/ml_data.util.h"
#include "../io/ddm/pima_indians_diabetes_reader.h"

double run_knn(std::vector<ClassificationData> test, std::vector<ClassificationData> training, size_t k)
{
	Knn knn;
	size_t correct = 0; 
	for (auto test_data : test)
	{
		std::string maxClass = knn.getNeighbours(test_data, training, k);
		if (maxClass.compare(test_data.clazz) == 0)
		{
			correct++;
		}
	}
	double success_ratio = static_cast<double>(100.0) *correct / static_cast<double>(test.size());
	/*
	std::cout << 
		correct << " of "<< test.size() << 
		" (" << success_ratio << ")" << std::endl;
	 */
	return success_ratio;
}

int main(int argc, char **argv)
{
	std::srand(std::time(NULL));

	size_t trial_count = 1;

	double success_ratio = 0;
	for (size_t i = 0; i < trial_count; i++)
	{
		auto dataset = read_iris_data();
		normalize(dataset);
		std::random_shuffle(dataset.begin(), dataset.end());
		auto splitted_data = split_data(dataset, 0.7);
		dataset.clear();
		success_ratio += run_knn(splitted_data.second, splitted_data.first, 10);
	}
	std::cout << "Iris, average success ratio: " << success_ratio / trial_count << std::endl;
	success_ratio = 0;

	for (size_t i = 0; i < trial_count; i++)
	{
		auto dataset = read_breast_cancer_data();
		normalize(dataset);
		std::random_shuffle(dataset.begin(), dataset.end());
		auto splitted_data = split_data(dataset, 0.7);
		dataset.clear();
		success_ratio += run_knn(splitted_data.second, splitted_data.first, 10);
	}
	std::cout << "Breast Cancer, average success ratio: " << success_ratio / trial_count << std::endl;
	success_ratio = 0;

	for (size_t i = 0; i < trial_count; i++)
	{
		auto dataset = read_pima_indians_diabetes_data();
		normalize(dataset);
		std::random_shuffle(dataset.begin(), dataset.end());
		auto splitted_data = split_data(dataset, 0.7);
		dataset.clear();
		success_ratio += run_knn(splitted_data.second, splitted_data.first, 10);
	}
	std::cout << "Diabetes, average success ratio: " << success_ratio / trial_count << std::endl;
	

	return 0;
}