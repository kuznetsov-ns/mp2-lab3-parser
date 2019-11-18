#pragma once

#include "stack.h"

template <class T>
class Queue
{
	T* pMem;
	int Size;
	int Start;
	int End;
public:
	Queue(int _size);
	Queue(const Queue& q);
	void push(T elem);
	T pop();
	bool isFull();
	bool isEmpty();
	void reverse(Queue<T>* q);
};

template <class T>
Queue<T>::Queue(int _size) : Size(_size)
{
	pMem = new T[Size];
	Start = 0;
	End = 1;
}

template <class T>
Queue<T>::Queue(const Queue& q)
{
	Size = q.Size;
	Start = q.Start;
	End = q.End;
	pMem = new T[Size];
	for (int i = Start; i != End; i = (i + 1) % Size)
		pMem[i] = q.pMem[i];
	if (!(isEmpty()))
		pMem[End] = q.pMem[End];
}

template <class T>
void Queue<T>::push(T elem)
{
	if (isFull()) throw "Full";
	Start = (Start + 1) % Size;
	pMem[Start] = elem;
}

template <class T>
T Queue<T>::pop()
{
	if (isEmpty()) throw "Empty";
	T tmp = pMem[End];
	End = (End + 1) % Size;
	return tmp;
}

template <class T>
bool Queue<T>::isFull()
{
	return(End == ((Start + 2) % Size));
}

template <class T>
bool Queue<T>::isEmpty()
{
	return(End == ((Start + 2) % Size));
}

template <class T>
void Queue<T>::reverse(Queue<T>* q)
{
	Stack<T> s(100);
	while (!q->isEmpty())
		s.push(q->pop());
	while (!s.isEmpty())
		q->push(s.pop());
}