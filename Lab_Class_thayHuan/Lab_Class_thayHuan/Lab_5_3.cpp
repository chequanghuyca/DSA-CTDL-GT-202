#include <iostream>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue {
	LH = -1,
	EH = 0,
	RH = 1
};

template<class T>
class AVLTree
{
public:
	class Node;
private:
	Node *root;
public:
	AVLTree() : root(nullptr) {}
	~AVLTree() {}

	void printInorder() {
		//TODO
	}

	bool search(const T &value) {
		//TODO
	}

	class Node
	{
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
