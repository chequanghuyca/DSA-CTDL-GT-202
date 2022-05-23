/*
In this question, you have to perform add and delete on binary search tree. Note that:
	- When deleting a node which still have 2 children, take the inorder successor (smallest node of the 
	right sub tree of that node) to replace it.
	- When adding a node which has the same value as parent node, add it in the left sub tree.
Your task is to implement two functions: add and deleteNode. You could define one or more functions to achieve this task.
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

template<class T>
class BinarySearchTree {
public:
	class Node;
private:
	Node* root;
public:
	BinarySearchTree() : root(nullptr) {}
	~BinarySearchTree() {
		// You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
	}
	//Helping function
	void add(T value) {
		//TODO
	}
	void deleteNode(T value) {
		//TODO
	}
	string inOrderRec(Node* root) {
		stringstream ss;
		if (root != nullptr) {
			ss << inOrderRec(root->pLeft);
			ss << root->value << " ";
			ss << inOrderRec(root->pRight);
		}
		return ss.str();
	}

	string inOrder() {
		return inOrderRec(this->root);
	}

	class Node {
	private:
		T value;
		Node* pLeft, *pRight;
		friend class BinarySearchTree<T>;
	public:
		Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
		~Node() {}
	};
};

int main() {
	BinarySearchTree<int> bst;
	bst.add(9);
	bst.add(2);
	bst.add(10);
	bst.add(8);
	/*cout << bst.inOrder() << endl;
	bst.add(11);
	bst.deleteNode(9);*/
	cout << bst.inOrder();
	return 0;
}