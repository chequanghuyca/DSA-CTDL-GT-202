#include<iostream>
#include<string>
#include<queue>
using namespace std;

template<class K, class V>
class BinaryTree {
public:
	class Node;

private:
	Node *root;

public:
	BinaryTree() : root(nullptr) {}
	~BinaryTree() {
		// You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
	}

	class Node {
	private:
		K key;
		V value;
		Node *pLeft, *pRight;
		friend class BinaryTree<K, V>;

	public:
		Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
		~Node() {}
	};

	void addNode(string posFromRoot, K key, V value) {
		if (posFromRoot == "") {
			this->root = new Node(key, value);
			return;
		}

		Node* walker = this->root;
		int l = posFromRoot.length();
		for (int i = 0; i < l - 1; i++) {
			if (!walker)
				return;
			if (posFromRoot[i] == 'L')
				walker = walker->pLeft;
			if (posFromRoot[i] == 'R')
				walker = walker->pRight;
		}
		if (posFromRoot[l - 1] == 'L')
			walker->pLeft = new Node(key, value);
		if (posFromRoot[l - 1] == 'R')
			walker->pRight = new Node(key, value);
	}
	/*
	Given a Binary tree, the task is to traverse all the nodes of 
	the tree using Breadth First Search algorithm and print the order of visited nodes 
	(has no blank space at the end)
	*/
	void BFS() {
		Node *a[100];
		int b[1000];
		int d = 0;
		int c = 0;
		int n = 0;
		a[0] = root;
		while (d <= c) {
			n++;
			b[n - 1] = a[d]->value;
			if (a[d]->pLeft != NULL) {
				c++;
				a[c] = a[d]->pLeft;
			}
			if (a[d]->pRight != NULL) {
				c++;
				a[c] = a[d]->pRight;
			}
			d++;
		}
		for (int i = 0; i < n - 1; i++) {
			cout << b[i] << " ";
		}
		cout << b[n - 1];
	}	
};

int main() {
	BinaryTree<int, int> binaryTree;
	binaryTree.addNode("", 2, 4); // Add to root
	binaryTree.addNode("L", 3, 6); // Add to root's left node
	binaryTree.addNode("R", 5, 9); // Add to root's right node
	binaryTree.BFS();
	return 0;
}