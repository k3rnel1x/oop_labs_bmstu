//
// Created by k3rnel1x on 17.03.2026.
//

#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <new>
#include <stdexcept>
#include <iostream>

namespace my {
using std::bad_alloc;
using std::runtime_error;
using std::invalid_argument;
using std::cout;
using std::endl;

template <typename T>
class mylist {
// Node
typedef struct Node {
    T*    data;
    Node* next;
    Node* prev;
} Node;

public:

    // Constructors - destructors
    mylist() = default;
    mylist(const mylist<T>& lst);
    mylist(std::initializer_list<T> lst);
    mylist(mylist<T>&& sample);
    ~mylist();

    // Methods
    int  get_len() 				  const;
    int  get_index(const T& elem) const;
    void add(const T& elem);
    void add_range(const mylist<T>& b);
    void add_range(T* arr, int size);
    T at(int index) const;
    void set_elem(int index,const T& elem);
    T&   get_elem(int index);
    void remove_elem(int index);
    void sort(int (*comp)(const T& r1, const T& r2));
    T*   to_array();
    mylist<T> combine(const mylist<T>& lst);

    // Оperators
    mylist<T>& operator =(const mylist<T>& sample);
    T& operator[](int index);

    // iterator
    class iterator {
    public:
        // Constructors - destructors
        iterator(mylist<T>& lst);

        iterator next();
         T    value();
        bool is_end();

        // Оperators
        iterator& operator++();
        T& operator*();
        // bool operator ==(iterator &b);
        bool operator!=(iterator &b);
    private:
        Node* _curr = NULL;
    };
    typedef my::mylist<T>::iterator Iter;

    iterator begin();
    iterator end();
protected:
    Node* _start = NULL;
};

}

#include "mylist.cpp"


#endif //LIST_H

