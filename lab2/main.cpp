//
// Created by k3rnel1x on 17.03.2026.
//
#include <iostream>
#include "mylist.h"
using std::cout;
using std::endl;
using my::mylist;

int cmp(const int& a, const int& b)
{
	return a - b;
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
	target_list_int.add(c + 2323);
	list_int.add_range(target_list_int);
	int mas[4] = {6, 7, 4, -1};
	list_int.add_range(mas, sizeof(mas)/sizeof(*mas));

    mylist<int>::iterator begin = list_int.begin();
    mylist<int>::iterator end = list_int.end();



	list_int.set_elem(3, -88);

	for (; begin != end; ++begin)
	{
		cout << "Elem: " << begin.value() << endl;
	}
	cout << "list_int.get_elem(5) = " << list_int.get_elem(5) << endl;

	cout << "****************** after removing 5 ******************" << endl;
	list_int.remove_elem(5);
	// mylist<int>::iterator begin = list_int.begin();
	for (auto iter = list_int.begin(); iter != end; ++iter)
	{
		cout << "Elem: " << iter.value() << endl;
	}

	cout << "****************** after sort ******************" << endl;
	list_int.sort(cmp);
	for (auto iter = list_int.begin(); iter != end; ++iter)
	{
		cout << "Elem: " << iter.value() << endl;
	}

	cout << "****************** ultra_new_list ******************" << endl;
	mylist<int> ultra_new_list(list_int);
	for (auto iter = ultra_new_list.begin(); iter != end; ++iter)
	{
		cout << "Elem: " << iter.value() << endl;
	}
}
