#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T>
class DLinkedList {
public:
	class Node;
protected:
	Node* head;
	Node* tail;
	int count;
public:
	DLinkedList() : head(NULL), tail(NULL), count(0) {};
	~DLinkedList() {};
	void    add(const T &e);
	void    add(int index, const T &e);
	int     size();
public:
	class Node {
	private:
		T data;
		Node *next;
		Node *previous;
		friend class DLinkedList<T>;

	public:
		Node() {
			this->previous = NULL;
			this->next = NULL;
		}

		Node(const T &data) {
			this->data = data;
			this->previous = NULL;
			this->next = NULL;
		}
	};
	string toString() {
		stringstream ss;
		ss << "[";
		Node *ptr = head;
		while (ptr != tail) {
			ss << ptr->data << ",";
			ptr = ptr->next;
		}
		if (count > 0) { ss << ptr->data << "]"; }
		else { ss << "]"; }
		return ss.str();
	}
};

template <class T>
void DLinkedList<T>::add(const T& e) {
	if (this->count == 0) {
		this->head = this->tail = new Node(e);
	}
	else {
		Node* newnode = new Node(e);
		newnode->previous = this->tail;
		this->tail = this->tail->next = newnode;
	}
	this->count++;
}
template<class T>
void DLinkedList<T>::add(int index, const T& e) {
	if (this->count == 0 || index >= this->count) { add(e); return; }
	else {
		if (index == 0) {
			Node* newnode = new Node(e);
			newnode->next = this->head;
			this->head->previous = newnode;
			this->head = newnode;
		}
		else {
			Node* p = this->head;
			for (int i = 0; i < index - 1; i++) {
				p = p->next;
			}
			Node* newnode = new Node(e);
			newnode->next = p->next;
			newnode->previous = p;
			p->next = p->next->previous = newnode;
		}
		this->count++;
	}
}
template<class T>
int DLinkedList<T>::size() {
	return this->count;
}

int main() {
	DLinkedList<int> list;
	int values[] = { 10, 15, 2,  6,  4,  7,  40,  8 };
	//                0   1   2   3   4   5   6    7
	int index[] = { 0,  0,  1,  3,  2,  3,  5,   0 };
	for (int idx = 0; idx < 8; idx++) {
		list.add(index[idx], values[idx]);
	}
	cout << list.toString();
	return 0;
}