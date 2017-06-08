#ifndef L3_DEQUE_H
#define L3_DEQUE_H
#include <iostream>
#include "L3_Container.h"
#include <string>
#include <sstream>

template <typename T>
class Deque : public virtual Container<T> {
	public:
		Deque (){};
		Deque (const Deque &object){};
		virtual void pushFront(T) = 0;
		virtual void pushBack(T) = 0;
		virtual T popFront() = 0;
		virtual T popBack() = 0;
		virtual T peekFront() const = 0;
		virtual T peekBack() const = 0;
		virtual T& peekFront() = 0;
		virtual T& peekBack() = 0;
		virtual ~Deque(){};
};

#endif
