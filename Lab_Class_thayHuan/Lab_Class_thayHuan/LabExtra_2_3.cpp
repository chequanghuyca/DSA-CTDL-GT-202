#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector> 
using namespace std;

string removeDuplicates(string s) {
	int i = 0, n = s.length();
	for (int j = 0; j < n; ++j, ++i) {
		s[i] = s[j];
		if (i > 0 && s[i - 1] == s[i]) {
			i -= 2;
		}
	}
	return s.substr(0, i);
}

int main() {
	cout << removeDuplicates("aasdss");
	return 0;
}