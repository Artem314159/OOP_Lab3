#ifndef L3_STATICARRAY_H
#define L3_STATICARRAY_H
#include <iostream>
#include "L3_Indexed.h"
#include <string>
#include <sstream>

template <typename T>
class StaticArrayIterator;

template <typename T>
class StaticArrayConstIterator;

template <typename T>
class StaticArray : public virtual IndexedContainer<T>{
	private:
		unsigned int arrSize = 0;
		T *sArr;
	public:
		friend class StaticArrayIterator<T>;
		friend class StaticArrayConstIterator<T>;
		Iterator<T> *createIterator(){ return new StaticArrayIterator<T>(*this); };
		ConstIterator<T> *createConstIterator() const{ return new StaticArrayConstIterator<T>(*this); };
		StaticArray<T> (const StaticArray<T> &s){
			arrSize = s.getSize();
			for(int i = 0; i < arrSize; i++)
			{ sArr[i] = s.get(i); }
		};
		~StaticArray<T>(){
			delete[] sArr;
		};
		StaticArray<T>& operator = (const StaticArray<T> &s){
	        if (this != &s)
	        {
	        	StaticArray<T>::~StaticArray<T>();
	        	StaticArray<T>(s);
			}
			return *this;
		};
		StaticArray(int size = 0) : arrSize(size){ sArr = new T[size]; };
		int getSize() const { return arrSize; };
		bool isEmpty() const { return getSize() == 0; };
		const char* toString(){
			stringstream s;
			for(int i = 0; i < arrSize; i++)
				s << sArr[i] << ", ";
			return s.str().c_str();
		};
		T get(unsigned int pos) const {
			if(pos < arrSize)
				return sArr[pos];
			else return NULL;
		};
		T& get(unsigned int pos){
			if(pos < arrSize)
				return sArr[pos];
			else return sArr[arrSize - 1];
		};
		void set(T elem, unsigned int pos){
			if(pos < arrSize)
				sArr[pos] = elem;
		};
};

template <typename T>
class StaticArrayIterator : public virtual Iterator<T>{
	private:
		T *array;
		int index = 0;
		int arrSize;
	public:
		StaticArrayIterator(StaticArray<T> &array):arrSize(array.getSize()){};
		T& next(){
			T &value = array[index];
			index++;
			return value;
		};
		bool hasNext() const{ return index < arrSize; };
		//StaticArrayIterator<T> *clone() const;
};

template <typename T>
class StaticArrayConstIterator : public virtual ConstIterator<T>{
	private:
		T *array;
		int index = 0;
		int arrSize;
	public:
		StaticArrayConstIterator(const StaticArray<T> &array):arrSize(array.getSize()){};
		const T& next(){
			T &value = array[index];
			index++;
			return value;
		};
		bool hasNext() const{ return index < arrSize; };
		//StaticArrayConstIterator<T> *clone() const;
};

#endif
