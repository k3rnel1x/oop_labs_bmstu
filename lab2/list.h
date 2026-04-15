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
using std::unique_ptr;

template <typename T>
class list {

// Node
public:
class iterator;
class Node {
friend class iterator;
friend class list;

public:
    Node(const T& val) : val(val) {};
    Node(T&& val) : val(val) {};

    Node() = default;
    ~Node() = default;
    Node(const Node& node) = default;
    Node(Node&& node) = default;
    Node& operator=(const Node& node) = default;
    Node& operator=(Node&& node) = default;

private:
    Node* next = nullptr;
    Node* prev = nullptr;
    T val;
};


class iterator {

friend list;

public:
    iterator(list& lst) : iterator(lst.begin()) {};
    iterator(Node* node) : current_node(node) {};
    iterator() = default;
    iterator(const iterator& iter) = default;
    iterator(iterator&& iter) = default;
    iterator& operator=(const iterator& iter) = default;
    iterator& operator=(iterator&& iter);
    // iterator&& operator-(int a);
    // iterator&& operator+(int a);


    iterator next();
    T value();
    bool is_end() const;

    // Оperators
    iterator& operator++();
    iterator& operator--();
    T& operator*();

    bool operator==(iterator& b) const;
    bool operator!=(const iterator& b) const;
    bool operator!=(const iterator&& b) const;
private:
    Node* current_node;
};


friend class iterator;
friend class Node;

public:
    list();
    list(const list& lst);              // copy
    list(std::initializer_list<T> init_lst); // init list
    list(list&& lst);                   // move
    ~list();                            // destroy

    int  get_len() const;
    int  indexof(const T& elem) const;
    void add(const T& elem);
    void add_range(const list& b);
    void add_range(T* arr, int size);
    inline T& at(int index);
    void set(int index,const T& elem);
    T   get(int index) const;
    void remove(int index);
    void remove(iterator& iter);
    void sort(int (*comp)(const T& r1, const T& r2));
    T*   to_array();
    list unit(const list& lst);

    list& operator=(const list& lst);
    bool operator==(const list& lst) const;
    T& operator[](int index);

    iterator begin();
    iterator end();

protected:
    void append(const T& val);
    void append(T&& val);
    inline void swap_iters(iterator& iter1, iterator& iter2);
    T& on_index(int index);
    void iter_deleter(iterator& del_iter);

private:
    int len = 0;
    Node* start_node;
    Node* end_node; // node after last

    iterator start_iterator;
    iterator end_iterator; // one after last
};

}

#include "list.cpp"
#include "iterator.cpp"

#endif //LIST_H


