#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

void bfs(vector<vector<int>> graph, int start) {
	int n = graph.size();
	vector<int> mark(n);
	queue<int> temp;
	queue<int> result;
	mark[start] = -1;
	result.push(start);
	for (auto i : graph[start]) {
		temp.push(i);
		mark[i] = 1;
	}
	while (temp.size()) {
		for (auto i : graph[temp.front()]) {
			if (mark[i] != 1 && mark[i] != -1) {
				temp.push(i);
				mark[i] = 1;
			}
		}
		result.push(temp.front());
		mark[temp.front()] = -1;
		temp.pop();
	}
	while (result.size() != 0) {
		cout << result.front() << " ";
		result.pop();
	}
}