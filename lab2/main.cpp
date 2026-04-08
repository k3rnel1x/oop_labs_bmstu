//
// Created by k3rnel1x on 17.03.2026.
//
#include <filesystem>
#include <iostream>
#include "list.h"
// using namespace std;
using namespace my;
using std::cout;
using std::endl;

int comp(const double& a, const double& b) { return a < b; }

int main(int argc, char* argv[])
{
	list<int> list_int = {1, 23, 4, 90};

#pragma section sec

	list<int> target_list_int;
	int c = 1488;
	target_list_int.add(c);
	target_list_int.add(c);
	list_int.add_range(target_list_int);
	int mas[4] = {6, 7, 4, -1};
	list_int.add_range(mas, sizeof(mas)/sizeof(*mas));
	for (auto iter = list_int.begin(); iter != list_int.end(); ++iter)
	{
	 cout << "Elem: " << iter.value() << endl;
	}

	list<double> target_to_copy = {4.0, 2.3, 1.0, 17.0, 5.2, 0.6, -133.0, 0.1};
	list<double> mylist_double;
	mylist_double = target_to_copy;
	cout << "mylist_double[1] = " << mylist_double[1] << endl;

	mylist_double.at(-1);

	bool exp = target_to_copy == mylist_double;
	cout << "Is target_to_copy == mylist_double? : " << exp << endl;

	// mylist_double = target_to_copy;
	cout << "_____________Before______________" << endl;
	for(double a : mylist_double)
	{
		cout << a << endl;
	}

	// mylist_double.sort(comp);

	cout << "______________After_____________" << endl;
	for(double a : mylist_double)
	{
		cout << a << endl;
	}

#pragma endsection
	return 0;
}
