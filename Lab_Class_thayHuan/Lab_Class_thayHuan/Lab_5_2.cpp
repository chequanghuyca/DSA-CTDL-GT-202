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

void printInteger(int &n)
{
	cout << n << " ";
}

template<class T>
class AVLTree
{
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
		if (t == NULL) { t = new Node(x); }
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
	Node* deleteRightBalance(Node* root, bool& shorter) {
		if (root->balance == LH) {
			root->balance = EH;		
		}
		else if (root->balance == EH) {
			root->balance = RH;
			shorter = 0;
		}
		else if (root->pRight != NULL) {
			Node* rightTree = root->pRight;
			if (rightTree->balance == LH) {
				Node* leftTree = rightTree->pLeft;
				if (leftTree->balance == LH) {
					rightTree->balance = RH;
					root->balance = EH;
				}
				else if (leftTree->balance == EH) {
					root->balance = LH;
					rightTree->balance = EH;
				}
				else {
					root->balance = LH;
					rightTree->balance = EH;
				}
				leftTree->balance = EH;
				root->pRight = rotateRight(rightTree);
				root = rotateLeft(root);
				}
			else {
				if (rightTree->balance != EH) {
					root->balance = EH;
					rightTree->balance = EH;
				}
				else {
					root->balance = RH;
					rightTree->balance = LH;
					shorter = 0;
				}
				root = rotateLeft(root);
			}
		}
		return root;
	}
	Node* deleteLeftBalance(Node* root, bool& shorter) {
		if (root->balane == RH) {
			root->balance = EH;
		}
		else if (root->balance == EH) {
				root->balance = LH;
				shorter = 0;
		}
		else if (root->pLeft != NULL) {
			Node* leftTree = root->pLeft;
			if (leftTree->balance == RH) {
				Node* rightTree = leftTree->pRight;
				if (rightTree->balance == LH) {
					leftTree->balance = LH;
					root->balance = EH;
				}
				else if (rightTree->balance == EH) {
					root->balance = RH;
					leftTree->balance = EH;
				}
				else {
					root->balance = RH;
						leftTree->balance = EH;
				}
				rightTree->balance = EH;
				root->pLeft = rotateRight(leftTree);
				root = rotateRight(root);
			}
			else {
				if (leftTree->balance != EH) {
					root->balance = EH;
					leftTree->balance = EH;
				}
				else {
					root->balance = LH;
					leftTree->balance = RH;
					shorter = 0;
				}
				root = rotateRight(root);
			}
		}
		return root;
	}
	Node* AVLDelete(Node* root, T deleteKey, bool& shorter, bool& success) {
			if (root == NULL) {
				shorter = 0;
				success = 0;
				return NULL;
			}
			if (deleteKey < root->data) {
				root->pLeft = AVLDelete(root->pLeft, deleteKey, shorter, success);
				if (shorter) root = deleteRightBalance(root, shorter);
			}
			else if (deleteKey > root->data) {
				root->pRight = AVLDelete(root->pRight, deleteKey, shorter, success);
				if (shorter)root = deleteRightBalance(root, shorter);
			}
		else {
			Node* deleteNode = root;
			if (root->pRight == NULL) {
				Node* newRoot = root->pLeft;
				success = true;
				shorter = true;
				delete deleteNode;
				return newRoot;
			}
			else if (root->pLeft == NULL) {
				Node* newRoot = root->pRight;
				success = true;
				shorter = true;
				delete deleteNode;
				return newRoot;
			}
			else {
				Node* exchPtr = root->pLeft;
				while (exchPtr->pRight != NULL) {
				exchPtr = exchPtr->pRight;
			}
				root->data = exchPtr->data;
				root->pLeft = AVLDelete(root->pLeft, exchPtr->data, shorter, success);
				if (shorter) root = deleteRightBalance(root, shorter);
			}
		}
		return root;
	}
	void remove(const T& value) {
		bool shorter = 0, success = 0;
		root = AVLDelete(root, value, shorter, success);
		//TODO
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
	int arr[] = { 10,52,98,32,68,92,40,13,42,63 };
	for (int i = 0; i < 10; i++) {
		avl.insert(arr[i]);
	}
	avl.remove(10);
	avl.printTreeStructure();
	return 0;
}