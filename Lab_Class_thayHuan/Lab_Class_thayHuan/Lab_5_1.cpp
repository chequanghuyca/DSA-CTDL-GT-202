#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue {
	LH = -1,
	EH = 0,
	RH = 1
};

void printNSpace(int n) {
	for (int i = 0; i < n - 1; i++)
		cout << " ";
}

void printInteger(int &n) {
	cout << n << " ";
}

template<class T>
class AVLTree {
public:
	class Node;
private:
	Node *root;
protected:
	int getHeightRec(Node *node) {
		if (node == NULL)
			return 0;
		int lh = this->getHeightRec(node->pLeft);
		int rh = this->getHeightRec(node->pRight);
		return (lh > rh ? lh : rh) + 1;
	}
public:
	AVLTree() : root(nullptr) {}
	~AVLTree() {}
	int getHeight() {
		return this->getHeightRec(this->root);
	}
	void printTreeStructure() {
		int height = this->getHeight();
		if (this->root == NULL) {
			cout << "NULL\n";
			return;
		}
		queue<Node *> q;
		q.push(root);
		Node *temp;
		int count = 0;
		int maxNode = 1;
		int level = 0;
		int space = pow(2, height);
		printNSpace(space / 2);
		while (!q.empty()) {
			temp = q.front();
			q.pop();
			if (temp == NULL) {
				cout << " ";
				q.push(NULL);
				q.push(NULL);
			}
			else {
				cout << temp->data;
				q.push(temp->pLeft);
				q.push(temp->pRight);
			}
			printNSpace(space);
			count++;
			if (count == maxNode) {
				cout << endl;
				count = 0;
				maxNode *= 2;
				level++;
				space /= 2;
				printNSpace(space / 2);
			}
			if (level == height)
				return;
		}
	}

	Node* singleRightRotate(Node*& t) {
		Node* u = t->pLeft;
		t->pLeft = u->pRight;
		u->pRight = t;
		return u;
	}

	Node* singleLeftRotate(Node*& t) {
		Node* u = t->pRight;
		t->pRight = u->pLeft;
		u->pLeft = t;
		return u;
	}
	Node* doubleLeftRotate(Node*& t) {
		t->pRight = singleRightRotate(t->pRight);
		return singleLeftRotate(t);
	}

	Node* doubleRightRotate(Node*& t) {
		t->pLeft = singleLeftRotate(t->pLeft);
		return singleRightRotate(t);
	}
	Node* inSert(const T& x, Node* t) {
		if (t == NULL) {
			t = new Node(x);
		}
		else if (x < t->data) {
			t->pLeft = inSert(x, t->pLeft);
			if (getHeightRec(t->pLeft) - getHeightRec(t->pRight) == 2) {
				if (x < t->pLeft->data)
					t = singleRightRotate(t);
				else
					t = doubleRightRotate(t);
			}
		}
		else if (x >= t->data) {
			t->pRight = inSert(x, t->pRight);
			if (getHeightRec(t->pRight) - getHeightRec(t->pLeft) == 2) {
				if (x >= t->pRight->data)
					t = singleLeftRotate(t);
				else
					t = doubleLeftRotate(t);
			}
		}
		return t;
	}
	void insert(const T& value) {
		this->root = inSert(value, this->root);
	}

	class Node {
	private:
		T data;
		Node *pLeft, *pRight;
		BalanceValue balance;
		friend class AVLTree<T>;

	public:
		Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
		~Node() {}
	};
};

int main() {
	AVLTree<int> avl;
	for (int i = 0; i < 9; i++) {
		avl.insert(i);
	}
	avl.printTreeStructure();
	return 0;
}