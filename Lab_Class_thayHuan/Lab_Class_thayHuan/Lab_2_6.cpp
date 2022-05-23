#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <class T>
class DLinkedList {
public:
	class Node;     //forward declaration
protected:
	Node* head;
	Node* tail;
	int count;
public:
	DLinkedList();
	~DLinkedList();
	void add(const T& e);
	void add(int index, const T& e);
	T removeAt(int index);
	bool removeItem(const T& removeItem);
	bool empty();
	int size();
	void clear();
	T get(int index);
	void set(int index, const T& e);
	int indexOf(const T& item);
	bool contains(const T& item);
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
template<class T>
T DLinkedList<T>::get(int index) {
	Node * pTemp = head;
	while (index > 0 && pTemp) {
		pTemp = pTemp->next;
		index--;
	}
	return pTemp->data;
}
template <class T>
void DLinkedList<T>::set(int index, const T& e) {
	if (index >= 0 || index < count) {
		Node * pTemp = head;
		while (index > 0) {
			pTemp = pTemp->next;
			index--;
		}
		pTemp->data = e;
	}
}
template<class T>
bool DLinkedList<T>::empty() {
	return count == 0;
}
template<class T>
int DLinkedList<T>::indexOf(const T& item) {
	int i = 0;
	Node * pTemp = head;
	while (pTemp) {
		if (pTemp->data == item) {
			return i;
		}
		pTemp = pTemp->next;
	}
	return -1;
}
template<class T>
bool DLinkedList<T>::contains(const T& item) {
	return indexOf(item) != -1;
}
template <class T>
T DLinkedList<T>::removeAt(int index) {
	T returnData;
	if (index > count) { throw std::out_of_range("Invalid Index"); }
	if (head == tail && index == 0) {
		returnData = head->data;
		delete head;
		head = NULL;
		tail = NULL;
		count--;
		return returnData;
	}
	if (index == 0) {
		returnData = head->data;
		head = head->next;
		delete head->previous;
		count--;
		return returnData;
	}
	if (index == count - 1) {
		count--;
		returnData = tail->data;
		tail = tail->previous;
		delete tail->next;
		return returnData;
	}
	int now = 0;
	Node *current = head;
	while (now < index) {
		now++;
		current = current->next;
	}
	count--;
	current->previous->next = current->next;
	current->next->previous = current->previous;
	returnData = current->data;
	delete current;
	return returnData;
}
template <class T>
bool DLinkedList<T>::removeItem(const T &item) {
	if (!contains(item) || !head)
		return false;
	removeAt(indexOf(item));
	return true;
}
template <class T>
void DLinkedList<T>::clear() {
	Node *current = head;
	Node *previous = head;
	while (current) {
		previous = current;
		current = current->next;
		delete previous;
	}
	head = NULL;
	tail = NULL;
	count = 0;
}

template<class T>
class Queue {
protected:
	DLinkedList<T> list;
public:
	Queue() {}
	void push(T item){ list.add(item); }
	T pop(){ return list.removeAt(0); }
	T top(){ return list.get(0); }
	bool empty(){ return list.empty(); }
	int size(){ return list.size(); }
	void clear(){ list.clear(); }
};
int main() {
	return 0;
}
