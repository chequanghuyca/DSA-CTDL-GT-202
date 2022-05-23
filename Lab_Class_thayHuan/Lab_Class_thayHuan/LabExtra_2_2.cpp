#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

int baseballScore(string ops) {
	stack<int> score;
	int t = ops.length();
	for (int i = 0; i < t; i++) {
		if (ops[i] >= 48 && ops[i] <= 57) {
			int x = ops[i] - '0';
			score.push(x);
		}
		if (ops[i] == 'C') {
			score.pop();
		}
		if (ops[i] == 'D') {
			int x = 2 * score.top();
			score.push(x);
		}
		if (ops[i] == '+') {
			int a = score.top();
			score.pop();
			int b = a + score.top();
			score.push(a);
			score.push(b);
		}
	}
	int ans = 0;
	int n = score.size();
	for (int i = 0; i < n; i++) { 
		ans += score.top(); score.pop(); 
	}
	return ans;
}

int main() {
	cout << baseballScore("524CD9++");
	return 0;
}