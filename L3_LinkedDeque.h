#ifndef L3_LINKEDDEQUE_H
#define L3_LINKEDDEQUE_H
#include <iostream>
#include "L3_Deque.h"
#include <string>
#include <sstream>

template <typename T>
class LinkedDequeIterator;

template <typename T>
class LinkedDequeConstIterator;

template <typename T>
class LinkedDeque : public virtual Deque<T>{
	private:
		unsigned int deqSize = 0;
		struct Node{
			T value;
			Node *next;
		};
		Node *front = NULL, *back = front;
	public:
		friend class LinkedDequeIterator<T>;
		friend class LinkedDequeConstIterator<T>;
		Iterator<T> *createIterator(){ return new LinkedDequeIterator<T>(*this); };
		ConstIterator<T> *createConstIterator() const{ return new LinkedDequeConstIterator<T>(*this); };
		LinkedDeque<T>& operator = (const LinkedDeque<T> &s){
	        if (this != &s)
	        {
	        	LinkedDeque<T>::~LinkedDeque<T>();
	        	LinkedDeque<T>(s);
			}
			return *this;
		};
		~LinkedDeque<T>(){
			while(front != NULL)
			{
				Node *newNode = front;
				front = front->next;
				delete newNode;
			}
		};
		LinkedDeque<T> (const LinkedDeque<T> &s){
			Node *newNode = s.front;
			front = new Node;
			Node *resNode = front;
			while(newNode->next != NULL)
			{
				front->value = newNode->value;
				front->next = new Node;
				front = front->next;
				newNode = newNode->next;
			}
			front->value = newNode->value;
			front = resNode;
		};
		//LinkedDeque(int size = 0) : deqSize(size){};
		int getSize() const{
			int size = 0;
			Node *newNode = front;
			while(newNode)
			{
				size++;
				newNode = newNode->next;
			}
			return size;
		};
		bool isEmpty() const{ return getSize() == 0; };
		const char* toString(){
			Node *sNode = front;
			string s = "";
			while(sNode != back)
			{
				stringstream stream;
				stream << sNode->value;
				s += stream.str() + ", ";
				sNode = sNode->next;
			}
			if(back != NULL)
			{
			    stringstream stream;
			    stream << back->value;
				s += stream.str() + ", ";
			}
			return s.c_str();
		};
		void setDeqSize(int Size){ deqSize = Size; };
		void pushFront(T elem){
			if(getSize() < deqSize)
			{
				if(front != NULL)
				{
					Node *newNode = new Node;
					newNode->value = elem;
					newNode->next = front;
					front = newNode;
				}
				else
				{
					Node *newNode = new Node;
					newNode->value = elem;
					newNode->next = NULL;
					front = newNode;
					back = newNode;
				}
			}
		};
		void pushBack(T elem){
			if(getSize() < deqSize)
			{
				if(back != NULL)
				{
					Node *newNode = new Node;
					newNode->value = elem;
					back->next = newNode;
					back = newNode;
					back->next = NULL;
				}
				else
				{
					Node *newNode = new Node;
					newNode->value = elem;
					newNode->next = NULL;
					front = newNode;
					back = newNode;
				}
			}
		};
		T popFront(){
			if (front != NULL)
			{
				T value = front->value;
				Node *popNode = front;
				front = front->next;
				delete popNode;
				return value;
			}
			else return NULL;
		};
		T popBack(){
			if (back != NULL)
			{
				T value = back->value;
				Node *popNode = front;
				for(int i = 0; i < getSize() - 1; i++)
					popNode = popNode->next;
				popNode->next = NULL;
				back = popNode;
				return value;
			}
			else return NULL;
		};
		T peekFront() const{
			if(front != NULL)
				return front->value;
			return 0;
		};
		T peekBack() const{
			if(front != NULL)
				return back->value;
			return 0;
		};
		T& peekFront(){ return front->value; };
		T& peekBack(){ return back->value; };
};

template <typename T>
class LinkedDequeIterator : public virtual Iterator<T>{
	private:
		typename LinkedDeque<T>::Node *front = NULL;
	public:
		LinkedDequeIterator(LinkedDeque<T> &lDeque):front(lDeque.front){};
		T& next(){
			T &value = front->value;
			front = front->next;
			return value;
		};
		bool hasNext() const{ return front != NULL; };
		//LinkedDequeIterator<T> *clone() const;
};

template <typename T>
class LinkedDequeConstIterator : public virtual ConstIterator<T>{
	private:
		typename LinkedDeque<T>::Node *front = NULL;
	public:
		LinkedDequeConstIterator(const LinkedDeque<T> &lDeque):front(lDeque.front){};
		const T& next(){
			T &value = front->value;
			front = front->next;
			return value;
		};
		bool hasNext() const{ return front != NULL; };
		//LinkedDequeConstIterator<T> *clone() const;
};

#endif
