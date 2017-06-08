#ifndef L3_PUSHPOP_H
#define L3_PUSHPOP_H
#include <iostream>
#include "L3_Container.h"
#include <string>
#include <sstream>

template <typename T>
class PushPopContainer : public virtual Container<T> {
	public:
		PushPopContainer (){};
		PushPopContainer (const PushPopContainer &object){};
		virtual void push(T) = 0;
		virtual T pop() = 0;
		virtual T peek() const = 0;
		virtual T& peek() = 0;
		virtual ~PushPopContainer(){};
};

#endif
