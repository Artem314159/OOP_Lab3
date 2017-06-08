#include <iostream>
#include "L3_LinkedList.h"
#include "L3_Stack.h"
#include "L3_Queue.h"
#include "L3_StaticArray.h"
#include "L3_LinkedDeque.h"
#include <Math.h>
using namespace std;

int main(int argc, char** argv) {
	Stack<int> *MyInt = new Stack<int>;
	Stack<char> *MyChar = new Stack<char>;
	for(int i = 0; i < 10; i++)
	{
		MyInt->push(i*sqrt(i));
		MyChar->push((char)(10*i + 20));
	}
	Stack<int> *NewMyInt = new Stack<int>;
	NewMyInt = new Stack<int>(*MyInt);
	NewMyInt->push(10);
	NewMyInt->Sort();
	cout << MyInt->toString() << "\n";
	cout << NewMyInt->toString() << "\n";
	cout << MyChar->toString();
	return 0;
}
