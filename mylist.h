//
// Created by k3rnel1x on 17.03.2026.
//

#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace my {
using std::bad_alloc;
using std::runtime_error;
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
    mylist();
    mylist(const mylist<T>& lst);
    // list(list<T>&& list);
    // explicit list(std::initializer_list<T> lst);
    ~mylist();

    // Methods
    int  get_len() const;
    int  get_index(const T& elem) const;
    void add(const T& elem);
    // void add_range(const list<T>& b);
    // void add_range(T* arr, int size);
    // void set_elem(int index,const T& elem);
    T&   get_elem(int index);
    // void remove_elem(int index);
    // void sort(int (*comp)(const T& r1, const T& r2));
    // T*   to_array();
    // list<T> combine(const list<T>& lst);


    // Оperators
    mylist<T>& operator =(const mylist<T>& sample);
    T& operator[](int index);

    // Iterator
    class Iterator {
    public:
        // Constructors - destructors
        Iterator(mylist<T> lst);

        // Methods
        Iterator next();
        T    value() const;
        bool is_end() const;

        // Оperators
        Iterator& operator++();
        T& operator*();
        bool operator ==(Iterator &b);
        bool operator !=(Iterator &b);
    private:
        Node* _curr = NULL;
    };
    typedef my::mylist<T>::Iterator Iter;

    Iterator begin() const;
    Iterator end() const;
protected:
    Node* _start = NULL;
};


// ********************** list ********************** //

template<typename T>
my::mylist<T>::mylist()
{
    // cout << "Run mylist()" << endl;
}

template<typename T>
my::mylist<T>::~mylist()
{
    if (!_start)
        return;
    // goto last node
    Node* last_node = _start;
    while (last_node->next != NULL) last_node = last_node->next;

    // start rising, clearing data and nodes
    Node* curr = last_node;
    while (curr->prev != NULL) {
        delete curr->data;
        curr = curr->prev;
        delete curr->next;
        curr->next = NULL;
    }

    // erase _start node
    delete _start->data;
    _start->data = NULL;
}

template<typename T>
my::mylist<T>::mylist(const mylist<T>& sample) : mylist()
{
    // get first elem iter of sample
    Iter sample_iter = sample.begin();
    Node* curr = _start;
    while (!sample_iter.is_end()) // while next node exists
    {
        // create next node
        try {
            curr->next = new Node;
        } catch (bad_alloc) {
            throw bad_alloc();
        }
        // copy curr data
        *(curr->data) = sample_iter.value();
        // move on next node
        curr = curr->next;
        ++sample_iter;
    }
}

// template<typename T>
// my::list<T>::list(std::initializer_list<T> lst) : list()
// {
//     // TODO i dont know ths shit
// }

template<typename T>
typename my::mylist<T>::Iterator my::mylist<T>::begin() const
{
    return my::mylist<T>::Iterator(*this);
}


template<typename T>
typename my::mylist<T>::Iterator my::mylist<T>::end() const
{
    auto iter = my::mylist<T>::Iterator(*this);
    while (*iter) ++iter;
    return iter;
}

template<typename T>
my::mylist<T>& my::mylist<T>::operator=(const mylist<T>& sample)
{
    // get first elem iter of sample
    Iter sample_iter = sample.begin();
    Node* curr = _start;
    while (!sample_iter.is_end()) // while next node exists
    {
        // create next node
        try {
            curr->next = new Node(0);
        } catch (bad_alloc) {
            throw bad_alloc();
        }
        // copy curr data
        *(curr->data) = *(sample_iter._curr->data);
        // move on next node
        curr = curr->next;
        sample_iter++;
    }
}

template<typename T>
T& my::mylist<T>::operator[](int index)
{
    Node* curr = _start;
    for (int i = 0; i < this->get_len(); i++) {
        if (index == i)
            return *(curr->data);
        curr = curr->next;
    }

    throw runtime_error("No elem by this index");
}

template<typename T>
int my::mylist<T>::get_len() const
{
    if (_start && _start->data && !_start->next)
        return 1;

    int i = 1;
    Node* curr = _start;
    while (curr->next) {
        curr = curr->next;
        i++;
    }

    return i;
}

template<typename T>
int my::mylist<T>::get_index(const T& elem) const
{
    int i = 0;
    Node* curr = _start;
    while (curr->next) {
        i++;
        if (curr == &elem)
            return i;
        curr = curr->next;
    }
    return -1;
}

template<typename T>
void my::mylist<T>::add(const T& elem)
{
    // if first node does not exist
    if (!_start)
    {
        try
        {
            _start = new Node;
            _start->data = new T;
        } catch (bad_alloc) {
            throw bad_alloc();
        }
        *(_start->data) = elem;
        _start->next = NULL;
        _start->prev = NULL;
        return;
    }

    // if exist create next node
    // alloc new node and data
    Node* new_node;
    try {
        new_node = new Node;
        new_node->data = new T;
    } catch (bad_alloc) {
        throw bad_alloc();
    }

    // copy data no new node
    *(new_node->data) = elem;

    // insert new node
    Node* end_node = _start;
    while (end_node->next) end_node = end_node->next;
    end_node->next = new_node;
}

template<typename T>
T& my::mylist<T>::get_elem(int index)
{
    Node* curr = _start;
    for (int i = 0; i < this->get_len(); i++) {
        if (index == i)
            return *(curr->data);
    }

    throw runtime_error("No elem by this index");
}


// ********************** Iterator ********************** //


template<typename T>
my::mylist<T>::Iterator::Iterator(mylist<T> lst)
{
    // this->_curr = lst._start;
    cout << "run Iterator(mylist<T> lst)" << endl;
}

template<typename T>
typename my::mylist<T>::Iterator my::mylist<T>::Iterator::next()
{
    _curr = _curr->next;
    return this;
}

template<typename T>
T my::mylist<T>::Iterator::value() const
{
    if (!_curr->data)
        throw runtime_error("data is null");
    return *(_curr->data);
}

template<typename T>
bool my::mylist<T>::Iterator::is_end() const
{
    return !_curr->data;
}

template<typename T>
typename my::mylist<T>::Iterator& my::mylist<T>::Iterator::operator++()
{
    _curr = _curr->next;
    return *this;
}

template<typename T>
T& my::mylist<T>::Iterator::operator*()
{
    if (!_curr->data)
        throw runtime_error("data is null");
    return *(_curr->data);
}

template<typename T>
bool my::mylist<T>::Iterator::operator==(my::mylist<T>::Iterator& b)
{
    return _curr == b._curr;
}

template<typename T>
bool my::mylist<T>::Iterator::operator!=(my::mylist<T>::Iterator& b)
{
    return _curr != b._curr;
}




}

#endif //LIST_H
