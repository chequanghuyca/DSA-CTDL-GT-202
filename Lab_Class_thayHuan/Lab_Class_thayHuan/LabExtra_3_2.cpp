#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;

template <class T>
class Sorting {
public:
	static void printArray(T *start, T *end) {
		long size = end - start + 1;
		for (int i = 0; i < size - 1; i++)
			cout << start[i] << ", ";
		cout << start[size - 1];
		cout << endl;
	}

	static void merge(T* left, T* middle, T* right) {
		int n = right - left + 1;
		T* temp = new T(n);
		T* l = left, *m = middle + 1;
		for (int i = 0; i < n; i++) {
			if (l > middle) { temp[i] = *m; m++; }
			else if (m > right) { temp[i] = *l; l++; }
			else if (*l < *m) { temp[i] = *l; l++; }
			else { temp[i] = *(m); m++; }
		}
		for (int i = 0; i < n; i++) {
			*(left + i) = temp[i];
		}
		Sorting::printArray(left, right);
	}
	static void mergeSort(T* start, T* end) {
		if (start == end) return;
		int n = ((end - start) / 2);
		mergeSort(start, start + n);
		mergeSort(start + n + 1, end);
		merge(start, start + n, end);
	}
};
#endif

int main() {
	int arr[] = { 0,2,4,3,1,4 };
	Sorting<int>::mergeSort(&arr[0], &arr[5]);
	return 0;
}