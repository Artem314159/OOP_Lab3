#ifndef L3_CONTAINER_H
#define L3_CONTAINER_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
class Iterator{
	public:
		Iterator(){};
		virtual T& next() = 0;
		virtual bool hasNext() const = 0;
		//virtual Iterator<T> *clone() const = 0;
		virtual ~Iterator(){};
};

template <typename T>
class ConstIterator{
	public:
		ConstIterator(){};
		virtual const T& next() = 0;
		virtual bool hasNext() const = 0;
		//virtual ConstIterator<T> *clone() const = 0;
		virtual ~ConstIterator(){};
};

template <typename T>
class Container{
	public:
		Container (){};
		Container (const Container &object){}
		virtual int getSize() const = 0;
		virtual bool isEmpty() const{
			if(getSize() == 0)
				return true;
			return false;
		};
		virtual const char* toString() = 0;
		friend class Iterator<T>;
		friend class ConstIterator<T>;
		virtual Iterator<T> *createIterator() = 0;
		virtual ConstIterator<T> *createConstIterator() const = 0;
		void Sort(){
			Iterator<T> *i1 = createIterator();
			int size = this->getSize();
			for(int i = 0; i < size; i++)
			{
				T& begin = i1->next();
				Iterator<T> *i2 = createIterator();
				for(int k = 0; k < i; k++)
				{ i2->next(); }
				while(i2->hasNext())
				{
					T&temp = i2->next();
					if(begin > temp)
						swap(begin, temp);
				}
				delete i2;
			}
			delete i1;
		}
		std::ostream& operator<<(ostream& os){
			os << this->toString();
		    return os;
		};
		virtual ~Container(){};
};

#endif
