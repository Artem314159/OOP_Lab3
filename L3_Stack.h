#ifndef L3_STACK_H
#define L3_STACK_H
#include <iostream>
#include "L3_PushPop.h"
#include <string.h>
#include <sstream>
using namespace std;

template <typename T>
class StackIterator;

template <typename T>
class StackConstIterator;

template <typename T>
class Stack : public virtual PushPopContainer<T>{
	private:
		struct Node{
			T value;
			Node *next;
		};
		Node *current = NULL;
	public:
		friend class StackIterator<T>;
		friend class StackConstIterator<T>;
		StackIterator<T> *createIterator(){ return new StackIterator<T>(*this); };
		StackConstIterator<T> *createConstIterator() const{ return new StackConstIterator<T>(*this); };
		Stack(){};
		~Stack(){
			while(current != NULL)
			{
				Node *newNode = current;
				current = current->next;
				delete newNode;
			}
		};
		Stack<T>& operator = (const Stack<T> &s){
	        if (this != &s)
	        {
	        	Stack<T>::~Stack<T>();
	        	Stack<T>(s);
			}
			return *this;
		};
		Stack<T> (const Stack<T> &s){
			Node *newNode = s.current;
			current = new Node;
			Node *resNode = current;
			while(newNode->next != NULL)
			{
				current->value = newNode->value;
				current->next = new Node;
				current = current->next;
				newNode = newNode->next;
			}
			current->value = newNode->value;
			current = resNode;
		};
		int getSize() const{
			int size = 0;
			Node *newNode = current;
			while(newNode)
			{
				size++;
				newNode = newNode->next;
			}
			return size;
		};
		bool isEmpty() const{ return getSize() == 0; };
		const char* toString(){
			StackIterator<T> *i1 = createIterator();
			string s = "";
			while(i1->hasNext())
			{
			    stringstream stream;
			    stream << i1->next();
				s += stream.str() + ", ";
			}
			return s.c_str();
		};
		void push(T elem){
			Node *pushNode = new Node;
			pushNode->value = elem;
			pushNode->next = current;
			current = pushNode;
		};
		T pop(){
			if (current != NULL)
			{
				T value = current->value;
				Node *popNode = current;
				current = current->next;
				delete popNode;
				return value;
			}
			else return NULL;
		};
		T peek() const{ return current->value; };
		T& peek() { return current->value; };
		
};

template <typename T>
class StackIterator : public virtual Iterator<T>{
	private:
		typename Stack<T>::Node *current = NULL;
	public:
		StackIterator(Stack<T> &stack):current(stack.current){};
		T& next(){
			T &value = current->value;
			current = current->next;
			return value;
		};
		bool hasNext() const{ return current != NULL; };
		//StackIterator<T> *clone() const;
};

template <typename T>
class StackConstIterator : public virtual ConstIterator<T>{
	private:
		typename Stack<T>::Node *current = NULL;
	public:
		StackConstIterator(const Stack<T> &stack):current(stack.current){};
		const T& next(){
			T &value = current->value;
			current = current->next;
			return value;
		};
		bool hasNext() const{ return current != NULL; };
		//StackConstIterator<T> *clone() const;
};

#endif
