#pragma once
#include <string>

const int MAX_SIZE = 100;

template <class T>
class Stack
{
	T* pMem;
	int Size;
	int Index;
public:
	Stack(int _size);
	Stack(const Stack& st);
	~Stack();
	void push(T elem);
	bool isFull();
	bool isEmpty();
	T pop();
	void reverse(Stack& st);
};

template <class T>
Stack<T>::Stack(int _size) : Size(_size)
{
	Index = -1;
	pMem = new T[Size];
}

template <class T>
Stack<T>::Stack(const Stack& st)
{
	Size = st.Size;
	Index = st.Index;
	pMem = new T[Size];
	for (int i = 0; i < Size; i++)
		pMem[i] = st.pMem[i];
}

template <class T>
Stack<T>::~Stack()
{
	delete[] pMem;
}

template <class T>
void Stack<T>::push(T elem)
{
	if (isFull()) throw ("Full");
	Index++;
	pMem[Index] = elem;
}

template <class T>
bool Stack<T>::isFull()
{
	return(Index == Size - 1);
}

template <class T>
bool Stack<T>::isEmpty()
{
	return(Index == -1);
}

template <class T>
T Stack<T>::pop()
{
	if (isEmpty()) throw "Empty";
	return pMem[Index--];
}

template <class T>
void Stack<T>::reverse(Stack& st)
{
	Stack tmp(st);
	while (!st.isEmpty())
		st.pop();
	while (!tmp.isEmpty())
		st.push(tmp.pop());
}