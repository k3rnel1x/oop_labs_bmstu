//
// Created by k3rnel1x on 17.03.2026.
//
#include <iostream>
#include "../mylist.h"
using std::cout;
using std::endl;
using my::mylist;

int main(int argc, char *argv[])
{
    mylist<int> list_int;
	for(int i = 0; i < 5; i++)
	{	
    	list_int.add(i);
	}
    // cout << "len: " << list_int[0] << endl;
	
    mylist<int> target_list_int;
	int c = 1488;
	target_list_int.add(c);
	target_list_int.add(c);
	list_int.add_range(target_list_int);
	int mas[4] = {6, 7, 4, -1};
	list_int.add_range(mas, sizeof(mas)/sizeof(*mas));
    mylist<int>::iterator begin = list_int.begin();
    mylist<int>::iterator end = list_int.end();
    for (; begin != end; ++begin)
    {
        cout << "Elem: " << begin.value() << endl;
    }
}
