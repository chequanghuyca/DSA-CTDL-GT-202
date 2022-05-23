/*
	Implement methods add, size in template class SLinkedList (which implements List ADT) 
	representing the singly linked list with type T with the initialized frame. 
	The description of each method is given in the code.
	Example

	TEST											RESULT	
	SLinkedList<int> list;							[0,1,2,3,4,5,6,7,8,9]
	int size = 10;
	for(int index = 0; index < size; index++){
		list.add(index);
	}	
	cout << list.toString();
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList {
public:
	class Node;
protected:
	Node* head;
	Node* tail;
	int count;
public:
	SLinkedList() : head(NULL), tail(NULL), count(0) {};
	~SLinkedList() { };
	void add(const T& e);
	void add(int index, const T& e);
	int size();
	string toString() {
		stringstream ss;
		ss << "[";
		Node* ptr = head;
		while (ptr != tail) {
			ss << ptr->data << ",";
			ptr = ptr->next;
		}
		if (count > 0)
			ss << ptr->data << "]";
		else
			ss << "]";
		return ss.str();
	}
public:
	class Node {
	private:
		T data;
		Node* next;
		friend class SLinkedList<T>;
	public:
		Node() {
			next = 0;
		}
		Node(Node* next) {
			this->next = next;
		}
		Node(T data, Node* next = NULL) {
			this->data = data;
			this->next = next;
		}
	};
};

template <class T>
void SLinkedList<T>::add(const T& e) {
	if (this->count == 0) {
		Node* newnode = new Node(e, NULL);
		this->tail = newnode;
		this->head = newnode;
	}
	else {
		Node* newnode = new Node(e, NULL);
		this->tail->next = newnode;
		this->tail = newnode;
	}
	this->count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
	if (this->count == 0 || index >= this->count) {
		add(e);
		return;
	}
	else if (index <= 0) {
		Node* newnode = new Node(e, this->head);
		this->head = newnode;
	}
	else {
		Node* pnode = this->head;
		for (int i = 0; i < index - 1; i++)   pnode = pnode->next;
		Node* newnode = new Node(e, pnode->next);
		pnode->next = newnode;
	}
	this->count++;
}
template<class T>
int SLinkedList<T>::size() {
	return this->count;
}

int main() {
	SLinkedList<int> list;
	int size = 5;
	int values[] = { 1,   2,   3,   4,   5 };
	int index[] = { 0,   1,   2,   3,   4 };
	for (int idx = 0; idx < size; idx++) {
		list.add(index[idx], values[idx]);
	}
	cout << list.toString() << endl;
	list.add(index[2], values[4]);
	cout << list.toString() << endl;
	return 0;
}