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
	~SLinkedList() { };
	void    add(const T& e);
	void    add(int index, const T& e);
	int     size();
	bool    empty();
	T       get(int index);
	void    set(int index, const T& e);
	int     indexOf(const T& item);
	bool    contains(const T& item);
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

template<class T>
T SLinkedList<T>::get(int index) {
	if (index < 0 || index>this->count) {
		throw std::out_of_range("Index is out of range");
	}
	Node* p = this->head;
	for (int i = 0; i < index; i++) {
		p = p->next;
	}
	return p->data;
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
	if (index < 0 || index >= this->count) {
		throw std::out_of_range("Index is out of range");
	}
	Node* p = this->head;
	for (int i = 0; i < index; i++) {
		p = p->next;
	}
	p->data = e;
}

template<class T>
bool SLinkedList<T>::empty() {
	return (this->head == NULL);
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
	Node* p = this->head;
	int n = 0;
	while (p != NULL) {
		if (p->data == item) {
			return n;
		}
		n++;
		p = p->next;
	}
	return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
	Node* p = this->head;
	while (p != NULL) {
		if (p->data == item) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}


int main() {
	SLinkedList<int> list;
	for (int i = 0; i < 10; ++i) {
		list.add(i);
	}
	assert(list.empty() == false);
	cout << list.toString();
	return 0;
}