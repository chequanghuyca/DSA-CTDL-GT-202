#include <iostream>
using namespace std;

template <class T>
class Sorting {
private:
	static T *Partition(T *start, T *end) {
		cout << "Quick sort: ";
		printArray(start, end);
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
		return j;
	}

public:
	static void printArray(T *start, T *end) {
		int size = end - start;
		for (int i = 0; i < size - 1; i++)
			cout << start[i] << ", ";
		cout << start[size - 1];
		cout << endl;
	}

	static void insertionSort(T *start, T *end) {
		cout << "Insertion sort: ";
		printArray(start, end);
		T* current = start + 1;
		while (current < end) {
			T temp = *current;
			T* walker = current - 1;
			while (walker >= start && *walker > * current) {
				*(walker + 1) = *walker;
				walker--;
			}
			*(walker + 1) = temp;
			current++;
		}
	}

	static void hybridQuickSort(T *start, T *end, int min_size) {
		if (end - start >= min_size && end > start) {
			T* p = Partition(start, end);
			hybridQuickSort(start, p, min_size);
			hybridQuickSort(p + 1, end, min_size);
		}
		else if (end > start) { insertionSort(start, end); }
	}
};

int main() {
	int array[] = { 30, 7, 20, 0, -13, 1, 19, 72 };
	int min_size = 3;
	Sorting<int>::hybridQuickSort(&array[0], &array[8], min_size);
	return 0;
}