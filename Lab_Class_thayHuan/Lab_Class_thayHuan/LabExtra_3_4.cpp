#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
	static void merge(T* start, T* middle, T* end) {
		int n = end - start + 1;
		T temp[n];
		T *l = start, *m = middle + 1;
		for (int i = 0; i < n; i++) {
			if (l > middle) {
				temp[i] = *m;
				m++;
			}
			else if (m >= end) {
				temp[i] = *l;
				l++;
			}
			else if (*l < *m) {
				temp[i] = *l;
				l++;
			}
			else {
				temp[i] = *(m);
				m++;
			}
		}
		for (int i = 0; i < n; i++) { *(start + i) = temp[i]; }
	}
	static void printArray(T *start, T *end) {
		int size = end - start;
		for (int i = 0; i < size - 1; i++)
			cout << start[i] << " ";
		cout << start[size - 1];
		cout << endl;
	}
public:
	static void InsertionSort(T* start, T* end) {
		T *current = start + 1;
		while (current < end) {
			T temp = *current;
			T *walker = current - 1;
			while (walker >= start && *walker > temp) {
				*(walker + 1) = *walker;
				walker = walker - 1;
			}
			*(walker + 1) = temp;
			current++;
		}
	}
	static void TimSort(T* start, T* end, int min_size) {
		if (end - start <= min_size || min_size <= 0) {
			InsertionSort(start, end);
			cout << "Insertion Sort: ";
			printArray(start, end);
			return;
		}
		T *s = start;
		while (s < end) {
			T *e;
			if (s + min_size >= end)
				e = end;
			else
				e = s + min_size;
			InsertionSort(s, e);
			s = s + min_size;
		}
		cout << "Insertion Sort: ";
		printArray(start, end);
		s = start;
		int size = min_size;
		int count = 1;
		while (size < end - start) {
			while (s < end) {
				T *r;
				if (s + (size * 2) > end)
					r = end;
				else
					r = s + (size * 2);
				merge(s, s + size - 1, r);
				cout << "Merge " << count << ": ";
				printArray(start, end);
				s = s + (size * 2);
				count += 1;
			}
			s = start;
			size = size * 2;
		}
	}
};
#endif

int main() {
	Sorting<int> s;
	int array[] = { 19, 20, 18, 17 ,12, 13, 14, 15, 1, 2, 9, 6, 4, 7, 11, 16, 10, 8, 5, 3 };
	int min_size = 4;
	s.TimSort(&array[0], &array[20], min_size);
	return 0;
}