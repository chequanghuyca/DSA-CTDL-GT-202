#ifndef SORTING_H
#define SORTING_H

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
	static void printArray(T* start, T* end) {
		int size = end - start;
		for (int i = 0; i < size; i++) {
			cout << start[i] << " ";
		}
		cout << endl;
	}
	static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total) {
		int size = end - start;
		if (cur_segment_total == 1) {
			for (int i = 1; i < size; i++) {
				int key = start[i];
				int j = i - 1;
				while (j >= 0 && start[j] > key) {
					start[j + 1] = start[j];
					j = j - 1;
				}
				start[j + 1] = key;
			}
		}
		else for (int i = 0; i < cur_segment_total; i++) {
			for (int j = i; j < size; j += cur_segment_total) {
				for (int t = j + cur_segment_total; t < size; t += cur_segment_total) {
					if (start[t] < start[j]) {
						T temp = start[t];
						start[t] = start[j];
						start[j] = temp;
					}
				}
			}
		}
		cout << cur_segment_total << " segments: ";
		printArray(start, end);
	 }

public:
	static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases) {
		for (int i = 0; i < num_phases; i++) {
			for (int j = i + 1; j < num_phases; j++) {
				if (num_segment_list[j] > num_segment_list[i]) {
					int temp = num_segment_list[j];
					num_segment_list[j] = num_segment_list[i];
					num_segment_list[i] = temp;
				}
			}
		}
		for (int i = 0; i < num_phases; i++) {
			sortSegment(start, end, i, num_segment_list[i]);
		}
	 }
};
#endif

int main() {
	int num_segment_list[] = { 1, 3, 5 };
	int num_phases = 3;
	int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };
	Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
	return 0;
}