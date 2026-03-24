//
// Created by k3rnel1x on 17.03.2026.
//
#include <cmath>
#include <iostream>
#include "mylist.h"
using std::cout;
using std::endl;
using my::mylist;
#define EPS 1e-6

int comp(const double& r1, const double& r2)
{
	return r1 - r2 > 0;
}


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

	mylist<double> mylist_double = {4.0, 2.3, 1.0, 0.0, 5.2, 0.6, -133.0, 0.1};
	cout << "___________________________" << endl;
	for(double a : mylist_double)
	{
		cout << a << endl;
	}
	mylist_double.sort(comp);

	cout << "___________________________" << endl;
	for(double a : mylist_double)
	{
		cout << a << endl;
	}
	return 0;
}
