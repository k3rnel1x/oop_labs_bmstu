//
// Created by k3rnel1x on 17.03.2026.
//
#include <iostream>
#include "mylist.h"
using std::cout;
using std::endl;
using my::mylist;

int main(int argc, char *argv[])
{
    mylist<int> list_int;
    int a = 1, b = 5;
	int mas[5] = {1, 2, 3, 4, 5};
	for(int i = 0; i < sizeof(mas)/sizeof(*mas); i++)
	{	
    	list_int.add(mas[i]);
	}
    // cout << "len: " << list_int[0] << endl;
    mylist<int>::iterator begin = list_int.begin();
    mylist<int>::iterator end = list_int.end();
    for (; begin != end; ++begin)
    {
        cout << "Elem: " << begin.value() << endl;
    }
}
