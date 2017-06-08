#ifndef L3_LINKEDLIST_H
#define L3_LINKEDLIST_H
#include <iostream>
#include "L3_PushPop.h"
#include "L3_Insertable.h"
#include <string>
#include <sstream>

template <typename T>
class LinkedListIterator;

template <typename T>
class LinkedListConstIterator;

template <typename T>
class LinkedList : public virtual PushPopContainer<T>, public virtual InsertableContainer<T>{
	private:
		struct Node{
			T value;
			Node *next;
		};
		Node *current = NULL;
	public:
		friend class LinkedListIterator<T>;
		friend class LinkedListConstIterator<T>;
		LinkedListIterator<T> *createIterator(){ return new LinkedListIterator<T>(*this); };
		LinkedListConstIterator<T> *createConstIterator() const{ return new LinkedListConstIterator<T>(*this); };
		LinkedList(){};
		~LinkedList<T>(){
			while(current != NULL)
			{
				Node *newNode = current;
				current = current->next;
				delete newNode;
			}
		};
		LinkedList<T>& operator = (const LinkedList<T> &s){
	        if (this != &s)
	        {
	        	LinkedList<T>::~LinkedList<T>();
	        	LinkedList<T>(s);
			}
			return *this;
		};
		LinkedList<T> (const LinkedList<T> &s){
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
		}
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
			Node *sNode = current;
			string s = "";
			while(sNode)
			{
			    stringstream stream;
			    stream << sNode->value;
				s += stream.str() + ", ";
				sNode = sNode->next;
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
		T peek() const{	return current->value; };
		T& peek() { return current->value; };
		void insertAt(T elem, unsigned int pos){
			if(pos < getSize())
			{ 
				Node *newNode = current;
				for(int i = 0; i < getSize() - pos - 1; i++)
				{ newNode = newNode->next; }
				Node *insNode = new Node;
				insNode->value = elem;
				insNode->next = newNode->next;
				newNode->next = insNode;
			}
			else push(elem);
		};
		T removeAt(unsigned int pos){
			T res = NULL;
			if(pos < getSize() - 1)
			{
				Node *newNode = current;
				for(int i = 0; i < getSize() - pos - 2; i++)
				{ newNode = newNode->next; }
				res = newNode->next->value;
				newNode->next = newNode->next->next;
			}
			else if(pos == getSize() - 1)
				res = pop();
			return res;
		};
		T get(unsigned int pos) const{
			T res = 0;
			if(pos < getSize())
			{
				Node *getNode = current;
				for(int i = 0; i < getSize() - pos - 1; i++)
					getNode = getNode->next;
				res = getNode->value;
			}
			return res;
		};
		T& get(unsigned int pos){
			T res = 0;
			if(pos < getSize())
			{
				Node *getNode = current;
				for(int i = 0; i < getSize() - pos - 1; i++)
					getNode = getNode->next;
				res = getNode->value;
			}
			return res;
		};
		void set(T elem, unsigned int pos){
			if(pos < getSize())
			{
				Node *getNode = current;
				for(int i = 0; i < getSize() - pos - 1; i++)
					getNode = getNode->next;
				getNode->value = elem;
			}
			else push(elem);
		};
};

template <typename T>
class LinkedListIterator : public virtual Iterator<T>{
	private:
		typename LinkedList<T>::Node *current = NULL;
	public:
		LinkedListIterator(LinkedList<T> &lList):current(lList.current){};
		T& next(){
			T &value = current->value;
			current = current->next;
			return value;
		};
		bool hasNext() const{ return current != NULL; };
		//LinkedListIterator<T> *clone() const;
};

template <typename T>
class LinkedListConstIterator : public virtual ConstIterator<T>{
	private:
		typename LinkedList<T>::Node *current = NULL;
	public:
		LinkedListConstIterator(const LinkedList<T> &lList):current(lList.current){};
		const T& next(){
			T &value = current->value;
			current = current->next;
			return value;
		};
		bool hasNext() const{ return current != NULL; };
		//LinkedListConstIterator<T> *clone() const;
};

#endif
