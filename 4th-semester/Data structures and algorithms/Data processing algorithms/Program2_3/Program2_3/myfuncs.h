#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "mystructs.h"

void MenuForChoices();
std::string getCase();

float getRandomNumber(float min, float max);
bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
void printDashes();
int* copyMyArray(DynamicArray& numbers);
void clear_copy(DynamicArray& numbers);
std::string getUserSortChoice();

std::string getUserShellSortingCountSteps(const int& max_count_steps);
std::string getUserValueSteps(const DynamicArray& numbers, const DynamicArray& mass_of_steps);
void userShellSortingWishes(const DynamicArray& numbers, DynamicArray& mass_of_steps);

bool checkBucketSortingIsPossible(const DynamicArray& numbers);
void generateRequiredBucketSortingArray(const DynamicArray& numbers);
void random_shuffle(const DynamicArray& numbers);
void userBucketSortingWishes(DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time, bool& sort_exit);

bool checkGenericBucketSortingAndRadixSortingIsPossible(const DynamicArray& numbers);
void generateRequiredGenericBucketSortingAndRadixSortingArray(const DynamicArray& numbers);

bool isEmpty(const DynamicArray& numbers);
void generateArray(DynamicArray& numbers);
void regenerateArray(DynamicArray& myArray);
void printArray(const DynamicArray& numbers);
void clear(DynamicArray& myArray);

void sortSelectionAndRuntimeCalculation(DynamicArray numbers, const int& algorithm_number);
void bubbleSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments);
void selectionSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments);
void insertionSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments);
void heapifyFromArray(const DynamicArray& numbers, const int& size_heap, int index_current_elem, int& number_of_comparisons, int& number_of_assignments);
void heapSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments);
void quickSorting(const DynamicArray& numbers, int left_border, int right_border, int& number_of_comparisons, int& number_of_assignments);
void shellSorting(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments);
void userShellSorting(const DynamicArray& numbers, const DynamicArray& mass_of_steps, int& number_of_comparisons, int& number_of_assignments);
void bucketSortingWithSecondArray(DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time);
void bucketSortingWithoutSecondArray(const DynamicArray& numbers, int& number_of_comparisons, int& number_of_assignments);
void genericBucketSorting(const DynamicArray& numbers, int& number_of_coparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time);
void deleteBuckets(Bucket*& buckets, const int& buckets_size);
void radixSorting(const DynamicArray& numbers, int& number_of_coparisons, int& number_of_assignments, clock_t& start_time, clock_t& end_time);

#endif /* MYFUNCS_H_ */