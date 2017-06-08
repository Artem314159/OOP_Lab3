#ifndef L3_INSERTABLE_H
#define L3_INSERTABLE_H
#include <iostream>
#include "L3_Indexed.h"
#include <string>
#include <sstream>

template <typename T>
class InsertableContainer : public virtual IndexedContainer<T> {
	public:
		InsertableContainer (){};
		InsertableContainer (const InsertableContainer &object){};
		virtual void insertAt(T, unsigned int) = 0;
		virtual T removeAt(unsigned int) = 0;
		virtual ~InsertableContainer(){};
};

#endif
