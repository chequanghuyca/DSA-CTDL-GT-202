#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
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
			if (!walker) { return; }
			if (posFromRoot[i] == 'L') { walker = walker->pLeft; }
			if (posFromRoot[i] == 'R') { walker = walker->pRight; }
		}
		if (posFromRoot[l - 1] == 'L') { walker->pLeft = new Node(key, value); }
		if (posFromRoot[l - 1] == 'R') { walker->pRight = new Node(key, value); }
	}
	/*
		Given class BinaryTree, you need to finish methods isBST() to determine if a tree is a binary search tree (BST)
	*/
	bool check(Node* start) {
		if (start == NULL) { return true; }
		if (start->pLeft == NULL) {
			if (start->pRight == NULL) { return true; }
			else {
				if (start->pRight->value >= start->value) { return check(start->pRight); }
			}
		}
		else {
			if (start->pRight == NULL) {
				if (start->pLeft->value < start->value) { return check(start->pLeft); }
			}
			else {
				if (start->pLeft->value < start->value && start->pRight->value >= start->value) {
					return check(start->pLeft) && check(start->pRight);
				}
			}
		}
		return false;
	}
	bool isBST() { return check(this->root); }
};

int main() {
	BinaryTree<int, int> binaryTree;
	binaryTree.addNode("", 2, 4);
	binaryTree.addNode("L", 3, 6);
	binaryTree.addNode("R", 5, 9);
	binaryTree.addNode("LL", 4, 10);
	binaryTree.addNode("LR", 6, -3);
	binaryTree.addNode("LLL", 7, 2);
	binaryTree.addNode("LLLR", 8, 7);
	binaryTree.addNode("RR", 9, 30);
	binaryTree.addNode("RL", 10, 307);
	binaryTree.addNode("RLL", 11, 2000);
	binaryTree.addNode("RLLL", 11, 2000);
	cout << binaryTree.isBST();
	return 0;
}