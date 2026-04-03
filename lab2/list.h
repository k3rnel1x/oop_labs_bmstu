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
class list {
// Node
typedef struct Node {
    T*    data;
    Node* next;
    Node* prev;
} Node;

public:
    // Constructors - destructors
    list() = default;
    list(const list& lst);              // copy
    list(std::initializer_list<T> lst); // init list
    list(list&& lst);                   // move
    ~list();                            // destroy

    // Methods
    int  get_len() const;
    int  indexof(const T& elem) const;
    void add(const T& elem);
    void add_range(const list& b);
    void add_range(T* arr, int size);
    T at(int index) const;
    void set(int index,const T& elem);
    T&   get(int index);
    void remove(int index);
    void sort(int (*comp)(const T& r1, const T& r2));
    T*   to_array();
    list&& combine(const list& lst);

    // Оperators
    list& operator=(const list& lst);
    T& operator[](int index);

    // iterator
    class iterator {
    friend list;
    public:
        // Constructors - destructors
        iterator(list& lst);
        iterator(const list& lst);

        iterator next();
        T value();
        bool is_end();

        // Оperators
        iterator& operator++();
        T& operator*();
        bool operator==(iterator &b);
        bool operator!=(iterator &b);
    protected:
        iterator& _next();
        T _value();
    // private:
        Node* _curr = nullptr;
    };
    iterator begin();
    iterator end();
protected:
    int _len = 0;
    T _at(int index) const;
    void _add(const T& elem);
    T&   _get(int index);
    Node* _start = nullptr;
    Node* _end   = nullptr;
};

}

#include "list.cpp"
#include "iterator.cpp"

#endif //LIST_H


