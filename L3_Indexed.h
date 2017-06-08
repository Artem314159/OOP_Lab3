#ifndef L3_INDEXED_H
#define L3_INDEXED_H
#include <iostream>
#include "L3_Container.h"
#include <string>
#include <sstream>

template <typename T>
class IndexedContainer : public virtual Container<T> {
	public:
		IndexedContainer (){};
		IndexedContainer (const IndexedContainer &object){};
		virtual T get(unsigned int) const = 0;
		virtual T& get(unsigned int) = 0;
		virtual void set(T, unsigned int) = 0;
		T operator[](int index){ return get(index); }
		virtual ~IndexedContainer(){};
};

#endif
