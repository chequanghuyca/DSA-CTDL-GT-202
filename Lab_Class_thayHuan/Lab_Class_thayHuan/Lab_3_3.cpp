#include <iostream>
using namespace std;

template <class T>
class Sorting {
public:
	static void printArray(T *start, T *end) {
		int size = end - start;
		for (int i = 0; i < size - 1; i++) {
			cout << start[i] << ", ";
		}
		cout << start[size - 1];
		cout << endl;
	}

	static void oddEvenSort(T *start, T *end) {
		bool isSorted = false;
		int size = end - start;
		while (!isSorted) {
			isSorted = true;
			for (int i = 0; i <= size - 2; i = i + 2) {
				if (*(start + i) > *(start + i + 1)) {
					T temp = *(start + i);
					*(start + i) = *(start + i + 1);
					*(start + i + 1) = temp;
					isSorted = false;
				}
			}
			for (int i = 1; i <= size - 2; i = i + 2) {
				if (*(start + i) > *(start + i + 1)) {
					T temp = *(start + i);
					*(start + i) = *(start + i + 1);
					*(start + i + 1) = temp;
					isSorted = false;
				}
			}
			printArray(start, end);
		}
		return;
	}
};

int main() {
	int arr[] = { 1,2,2 };
	Sorting<int>::oddEvenSort(&arr[0], &arr[3]);
	return 0;
}