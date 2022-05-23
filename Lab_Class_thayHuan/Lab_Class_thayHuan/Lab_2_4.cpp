#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T>
class DLinkedList {
public:
	class Node;
	class Iterator;
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
	bool    empty();
	T       get(int index);
	void    set(int index, const T &e);
	int     indexOf(const T &item);
	bool    contains(const T &item);
	T       removeAt(int index);
	bool    removeItem(const T &item);
	void    clear();
	Iterator begin() {
		return Iterator(this, true);
	}
	Iterator end() {
		return Iterator(this, false);
	}
public:
	class Node {
	private:
		T data;
		Node *next;
		Node *previous;
		friend class DLinkedList<T>;
		Iterator begin() {
			return Iterator(this, true);
		}
		Iterator end() {
			return Iterator(this, false);
		}
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
	class Iterator {
	private:
		DLinkedList<T> *pList;
		Node *current;
		int index;
	public:
		Iterator(DLinkedList<T> *pList, bool begin);
		Iterator &operator=(const Iterator &iterator);
		void set(const T &e);
		T &operator*();
		bool operator!=(const Iterator &iterator);
		void remove();
		Iterator &operator++();
		Iterator operator++(int);
	};
	string toString() {
		stringstream ss;
		ss << "[";
		Node *ptr = head;
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
};

template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) {
	this->pList = pList;
	if (begin) {
		current = pList->head;
	}
	else {
		current = NULL;
	}
}
template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator) {
	this->pList = iterator.pList;
	this->current = iterator.current;
	return *this;
}
template <class T>
void DLinkedList<T>::Iterator::set(const T &e) {
	current->data = e;
}
template <class T>
T &DLinkedList<T>::Iterator::operator*() {
	return current->data;
}
template <class T>
void DLinkedList<T>::Iterator::remove() {
	int k = pList->indexOf(current->data);
	if (k != 0) current = current->previous;
	else current = pList->head;
	pList->removeAt(k);
}
template <class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator) {
	return current != iterator.current;
}
template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator++() {
	current = current->next;
	return *this;
}
template <class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int) {
	Iterator p = *this;
	current = current->next;
	return p;
}

int main() {
	DLinkedList<int> list;
	int size = 10;
	for (int idx = 0; idx < size; idx++) {
		list.add(idx);
	}
	DLinkedList<int>::Iterator it = list.begin();
	for (; it != list.end(); it++) {
		cout << *it << " |";
	}
	return 0;
}