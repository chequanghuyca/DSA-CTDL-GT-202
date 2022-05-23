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
	Node* root;
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
	// STUDENT ANSWER BEGIN 
	int getHeight(Node * pRoot) {
		if (pRoot == nullptr) { return -1; }
		else {
			int leftHeight = getHeight(pRoot->pLeft);
			int rightHeight = getHeight(pRoot->pRight);
			if (leftHeight > rightHeight) { return leftHeight + 1; }
			return rightHeight + 1;
		}
	}
	int getHeight() { // TODO: return height of the binary tree.
		if (this->root == nullptr) { return 0; }
		else { return getHeight(this->root); }
	}

	void preOrder(stringstream & ss, Node * pRoot) { // TODO: return the sequence of values of nodes in preorder.
		if (pRoot == nullptr) { return; }
		ss << pRoot->value << ' ';
		preOrder(ss, pRoot->pLeft);
		preOrder(ss, pRoot->pRight);
	}
	void inOrder(stringstream & ss, Node * pRoot) { // TODO: return the sequence of values of nodes in pre-order.
		if (pRoot == nullptr) { return; }
		inOrder(ss, pRoot->pLeft);
		ss << pRoot->value << ' ';
		inOrder(ss, pRoot->pRight);
	}
	void postOrder(stringstream & ss, Node * pRoot) { // TODO: return the sequence of values of nodes in pre-order.
		if (pRoot == nullptr) {	return;	}
		postOrder(ss, pRoot->pLeft);
		postOrder(ss, pRoot->pRight);
		ss << pRoot->value << ' ';
	}
	string preOrder() {
		stringstream ss;
		preOrder(ss, this->root);
		return ss.str();
	}
	string inOrder() { // TODO: return the sequence of values of nodes in in-order.
		stringstream ss;
		inOrder(ss, this->root);
		return ss.str();
	}
	string postOrder() { // TODO: return the sequence of values of nodes in post-order.
		stringstream ss;
		postOrder(ss, this->root);
		return ss.str();
	}
};

int main() {
	BinaryTree<int, int> binaryTree;
	binaryTree.addNode("", 2, 4); // Add to root
	binaryTree.addNode("L", 3, 6); // Add to root's left node
	binaryTree.addNode("R", 5, 9); // Add to root's right node
	cout << binaryTree.getHeight() << endl;
	cout << binaryTree.preOrder() << endl;
	cout << binaryTree.inOrder() << endl;
	cout << binaryTree.postOrder() << endl;
	return 0;
}