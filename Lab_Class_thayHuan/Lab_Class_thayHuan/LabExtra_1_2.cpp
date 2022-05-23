/*
	Implement Iterator class in class SLinkedList.

	Note: Iterator is a concept of repetitive elements on sequence structures.
	Iterator is implemented in class vector, list in STL container in C++ (https://www.geeksforgeeks.org/iterators-c-stl/).
	Your task is to implement the simple same class with iterator in C++ STL container.

Please read example and testcase carefully.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include<iterator> // for iterators 
using namespace std;

template <class T>
class SLinkedList {
public:
	class Iterator; //forward declaration
	class Node;     //forward declaration

protected:
	Node *head;
	Node *tail;
	int count;

public:
	SLinkedList() : head(NULL), tail(NULL), count(0) {};
	~SLinkedList();
	void add(const T &e);
	void add(int index, const T &e);
	T removeAt(int index);
	bool removeItem(const T &removeItem);
	bool empty();
	int size();
	void clear();
	T get(int index);
	void set(int index, const T &e);
	int indexOf(const T &item);
	bool contains(const T &item);
	string toString();

	SLinkedList(const SLinkedList &list) {
		this->count = 0;
		this->head = NULL;
		this->tail = NULL;
	}

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
		friend class SLinkedList<T>;

	public:
		Node() {
			next = 0;
		}
		Node(Node *next) {
			this->next = next;
		}
		Node(T data, Node *next = NULL) {
			this->data = data;
			this->next = next;
		}
	};

	class Iterator {
	private:
		SLinkedList<T>* pList;
		Node* current;
		int index;

	public:
		Iterator(SLinkedList<T>* pList = NULL, bool begin = true);
		Iterator& operator=(const Iterator& iterator);
		void remove();
		void set(const T& e);
		T& operator*();
		bool operator!=(const Iterator& iterator);
		Iterator& operator++();
		Iterator operator++(int);
	};
};

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin) {
	this->pList = pList;
	if (begin) {
		if (pList != NULL) {
			this->current = this->pList->head;
			this->index = 0;
		}
		else {
			this->current = NULL;
			this->index = -1;
		}
	}
	else {
		this->current = NULL;
		if (pList != NULL) this->index = this->pList->size();
		else this->index = 0;
	}
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator) {
	this->current = iterator.current;
	this->pList = iterator.pList;
	this->index = iterator.index;
	return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove() {
	if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
	else if (this->index == 0) {
		this->pList->removeAt(this->index);
		this->current = NULL;
		this->index = -1;
	}
	else {
		this->current = this->pList->head;
		for (int i = 0; i < this->index - 1; i++) {
			this->current = this->current->next;
		}
		this->pList->removeAt(this->index);
		this->index -= 1;
	}
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e) {
	if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
	this->current->data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*() {
	return this->current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator) {
	return !(this->current == iterator.current);
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++() {
	if (this->index == -1) this->current = this->pList->head;
	else this->current = this->current->next;
	this->index++;
	return *this;
}

template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int) {
	Iterator tmp = *this;
	if (this->index == -1) this->current = this->pList->head;
	else this->current = this->current->next;
	this->index++;
	return tmp;
}

int main() {
	SLinkedList<int> list;
	int size = 10;
	for (int idx = 0; idx < size; idx++) {
		list.add(idx);
	}
	SLinkedList<int>::Iterator it;
	int expvalue = 0;
	for (it = list.begin(); it != list.end(); it++) {
		assert(*it == expvalue);
		expvalue += 1;
	}
	return 0;
}