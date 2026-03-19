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
    int a = 1, b = 5;
    list_int.add(a);
    list_int.add(b);
    // cout << "len: " << list_int[0] << endl;
    // mylist<int>::Iterator begin(list_int);
    // mylist<int>::Iterator end = list_int.end();
    // for (; begin != end; ++begin)
    // {
    //     // cout << "Elem: " << begin.value() << endl;
    // }
}
