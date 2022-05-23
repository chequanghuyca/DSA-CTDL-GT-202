#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class V, int M> // K: key, V: data, M: order
class BTree {
	/// Convention: left < key <= right

public:
	class Entry;
	class Node;

private:
	Node* pRoot;

public:
	BTree() : pRoot(0) { };
	void clear(Node* & pRoot) { }
	void clear() { }
	~BTree() { }

	///////////////////////////////////////////////////
	///             CLASS `Entry`                   ///
	///////////////////////////////////////////////////
public:
	class Entry {
	private:
		K key;
		V value; // accept all type
		Node* rightPtr;
		friend class BTree<K, V, M>;

	public:
		Entry(K key = K{}, V value = V{}) : key(key), value(value), rightPtr(0) { }
		~Entry() { }

		string toString() {
			stringstream ss;
			// Hidden code
			return ss.str();
		}
	};

	///////////////////////////////////////////////////
	///             CLASS `Node`                    ///
	///////////////////////////////////////////////////
public:
	class Node {
	private:
		Entry entries[M - 1];
		Node* firstPtr;
		int numEntries;
		friend class BTree<K, V, M>;

	public:
		Node() : firstPtr(0), numEntries(0) { };
		~Node() { }
		bool isFull() { return (numEntries >= M - 1); }

		string toString() {
			stringstream ss;
			// Hidden code
			return ss.str();
		}
	};

	/////////////////////////////////////////////////////////////
	///         CLASS `BTree`: method implementation          ///
	/////////////////////////////////////////////////////////////
public:

	/// insert(inKey, inValue)
	/// BEGIN STUDENT CODE
	// Helping function

	BTree *insertIntoBST(BTree* root, int val) {
		if (root == nullptr)
			return new TreeNode(val);
		else if (root->val < val)
			root->right = insertIntoBST(root->right, val);
		else if (root->val > val)
			root->left = insertIntoBST(root->left, val);

		return root;
	}

	void insert(const K& inKey, const V& inValue) {
		this->root = insertIntoBST(value, this->root);
	}
	/// END STUDENT CODE

};

int main() {
	BTree<int, int, 3> bTree;
	int keys[] = { 78, 21, 14 };
	int size = sizeof(keys) / sizeof(int);

	for (int idx = 0; idx < size; idx++) {
		bTree.insert(keys[idx], idx);
	}

	cout << bTree.toStringInOrder() << endl;
	return 0;
}