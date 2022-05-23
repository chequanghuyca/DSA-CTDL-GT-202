#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
	static T* Partition(T* start, T* end) {
		T* p = start;
		T* i = start;
		T* j = end;
		while (i < j) {
			do {
				i = i + 1;
			} while (*i < *p);
			do {
				j = j - 1;
			} while (*j > * p);
			T temp = *i;
			*i = *j;
			*j = temp;
		}
		if (i >= j) {
			T temp = *i;
			*i = *j;
			*j = temp;
		}
		T temp = *p;
		*p = *j;
		*j = temp;
		cout << j - start << " ";
		return j;
	}
public:
	static void QuickSort(T* start, T* end) {
		if (start < end) {
			T* p = Partition(start, end);
			QuickSort(start, p);
			QuickSort(p + 1, end);
		}
	}
};
#endif

int main() {
	Sorting<int> s;
	int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
	cout << "Index of pivots: ";
	s.QuickSort(&array[0], &array[20]);
	cout << "\n";
	cout << "Array after sorting: ";
	for (int i : array) cout << i << " ";
	return 0;
}