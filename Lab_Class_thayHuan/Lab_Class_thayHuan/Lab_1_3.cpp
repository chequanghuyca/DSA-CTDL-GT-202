#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
using namespace std;

template <class T>
class SLinkedList {
public:
	class Node; // Forward declaration
protected:
	Node* head;
	Node* tail;
	int count;
public:
	SLinkedList() : head(NULL), tail(NULL), count(0) {};
	~SLinkedList() { this->clear(); };
	void    add(const T& e);
	void    add(int index, const T& e);
	int     size();
	bool    empty();
	void    clear();
	T       get(int index);
	void    set(int index, const T& e);
	int     indexOf(const T& item);
	bool    contains(const T& item);
	T       removeAt(int index);
	bool    removeItem(const T &removeItem);
	string  toString() {
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
T SLinkedList<T>::removeAt(int index) {
	if (index >= this->count || index < 0) throw out_of_range("");
	if (index == 0 && this->count == 1) {
		Node* p = this->head;
		T e = p->data;
		delete p;
		this->head = NULL;
		this->tail = NULL;
		this->count--;
		return e;
	}
	if (index == 0 && this->count != 1) {
		Node* p = this->head;
		T e = p->data;
		this->head = p->next;
		delete p;
		this->count--;
		return e;
	}
	if (index == this->count - 1) {
		Node* p = this->head;
		Node* tmp = this->tail;
		T e = this->tail->data;
		while (p->next != this->tail) {
			p = p->next;
		}
		delete tmp;
		this->tail = p;
		this->count--;
		return e;
	}
	Node* p = this->head;
	for (int i = 0; i < index - 1; i++) {
		p = p->next;
	}
	T e = p->next->data;
	Node* tmp = p->next;
	p->next = p->next->next;
	delete tmp;
	this->count--;
	return e;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item) {
	if (this->head == NULL) return 0;
	Node* preNode = NULL;
	Node* currentNode = this->head;
	bool t = 0;
	while (currentNode != NULL) {
		if (currentNode->data == item) {
			if (preNode == NULL) {
				// delete front
				this->head = currentNode->next;
				if (this->head == NULL) {
					this->tail = NULL;

				}
			}
			else if (this->tail == currentNode) {
				// delete last
				if (preNode != NULL) {
					preNode->next = NULL;
				}
				this->tail = preNode;
			}
			else {
				// delete in the middle
				preNode->next = currentNode->next;
			}
			//this->display();
			free(currentNode);
			t = 1;
		}
		if (t == 1) { break; }
		preNode = currentNode;
		currentNode = currentNode->next;
	}
	return t;
}

template<class T>
void SLinkedList<T>::clear() {
	while (this->head != NULL) {
		Node* currentNode = this->head;
		this->head = this->head->next;
		delete currentNode;
	}
	this->count = 0;
}

int main() {
	SLinkedList<int> list;
	for (int i = 0; i < 10; ++i) {
		list.add(i);
	}
	assert(!list.removeItem(-5));
	cout << list.toString();
	return 0;
}