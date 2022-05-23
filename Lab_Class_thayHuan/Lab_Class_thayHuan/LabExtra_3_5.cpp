#ifndef SORTINGAPPLICATION_H
#define SORTINGAPPLICATION_H
#include <iostream>
#include <string>
using namespace std;

bool isPermutation(string a, string b) {
	int la = a.length(), lb = b.length();
	if (la != lb)
		return 0;
	else {
		for (int i = 0; i < la; i++) {
			for (int j = i + 1; j < la; j++) {
				if (a[j] < a[i]) {
					char temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}
		for (int i = 0; i < lb; i++) {
			for (int j = i + 1; j < lb; j++) {
				if (b[j] < b[i]) {
					char temp = b[i];
					b[i] = b[j];
					b[j] = temp;
				}
			}
		}
		if (a == b)
			return 1;
		else
			return 0;

	}
}
#endif
int main() {
	string a = "abba";
	string b = "baba";
	cout << isPermutation(a, b);
	return 0;
}