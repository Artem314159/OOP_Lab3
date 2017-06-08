#ifndef L3_QUEUE_H
#define L3_QUEUE_H
#include <iostream>
#include "L3_PushPop.h"
#include <string>
#include <sstream>

template <typename T>
class QueueIterator;

template <typename T>
class QueueConstIterator;

template <typename T>
class Queue : public virtual PushPopContainer<T>{
	private:
		struct Node{
			T value;                                    
 			Node *prev;
		};
		Node *head = NULL;
		Node *current = head;
	public:
		friend class QueueIterator<T>;
		friend class QueueConstIterator<T>;
		QueueIterator<T> *createIterator(){ return new QueueIterator<T>(*this); };
		QueueConstIterator<T> *createConstIterator() const{ return new QueueConstIterator<T>(*this); };
		Queue(){};
		~Queue<T>(){
			while(head != NULL)
			{
				Node *newNode = head;
				head = head->prev;
				delete newNode;
			}
		};
		Queue<T>& operator = (const Queue<T> &s){
	        if (this != &s)
	        {
	        	Queue<T>::~Queue<T>();
	        	Queue<T>(s);
			}
			return *this;
		};
		Queue<T> (const Queue<T> &s){
			Node *newNode = s.head;
			head = new Node;
			current = head;
			//Node *resNode = head;
			while(newNode->prev != NULL)
			{
				current->value = newNode->value;
				current->prev = new Node;
				current = current->prev;
				newNode = newNode->prev;
			}
			current->value = newNode->value;
			//current = resNode;
		}
		int getSize() const{
			int size = 0;
			Node *newNode = head;
			while(newNode)
			{
				size++;
				newNode = newNode->prev;
			}
			return size;
		};
		bool isEmpty() const { return getSize() == 0; };
		const char* toString(){
			Node *sNode = head;
			string s = "";
			while(sNode)
			{
			    stringstream stream;
			    stream << sNode->value;
				s += stream.str() + ", ";
				sNode = sNode->prev;
			}
			return s.c_str();
		};
		void push(T elem){
			Node *pushNode = new Node;
			pushNode->value = elem;
			if (head != NULL)
			{
				current->prev = pushNode;
				current = current->prev;
				current->prev = NULL;
			}
			else
			{
				head = pushNode;
				current = pushNode;
				current->prev = NULL;
			}
		};
		T pop(){
			if (head != NULL)
			{
				T value = head->value;
				Node *popNode = head;
				head = head->prev;
				if(head == NULL)
				{ 
					current = head;
				}
				delete popNode;
				return value;
			}
			return NULL;
		};
		T peek() const { return head->value; };
		T& peek() { return current->value; };
};

template <typename T>
class QueueIterator : public virtual Iterator<T>{
	private:
		typename Queue<T>::Node *head = NULL;
	public:
		QueueIterator(Queue<T> &queue):head(queue.head){};
		T& next(){
			T &value = head->value;
			head = head->prev;
			return value;
		};
		bool hasNext() const{ return head != NULL; };
		//QueueIterator<T> *clone() const;
};

template <typename T>
class QueueConstIterator : public virtual ConstIterator<T>{
	private:
		typename Queue<T>::Node *head = NULL;
	public:
		QueueConstIterator(const Queue<T> &queue):head(queue.head){};
		const T& next(){
			T &value = head->value;
			head = head->prev;
			return value;
		};
		bool hasNext() const{ return head != NULL; };
		//QueueConstIterator<T> *clone() const;
};

#endif
