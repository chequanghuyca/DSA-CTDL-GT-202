#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class T>
class Heap {
protected:
	T* elements;
	int capacity;
	int count;
public:
	Heap()
	{
		this->capacity = 10;
		this->count = 0;
		this->elements = new T[capacity];
	}
	~Heap()
	{
		delete[]elements;
	}
	void push(T item);
	int getItem(T item);
	void remove(T item);
	void clear();
	void printHeap()
	{
		cout << "Max Heap [ ";
		for (int i = 0; i < count; i++)
			cout << elements[i] << " ";
		cout << "]\n";
	}
private:
	void ensureCapacity(int minCapacity);
	void reheapUp(int position);
	void reheapDown(int position);
};

// Your code here