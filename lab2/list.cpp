//
// Created by k3rnel1x on 17.03.2026.
//
#ifndef LIST_H
#include "list.h"
#endif

// ********************** list ********************** //
namespace my {

template<typename T>
list<T>::list(const list& lst) : list()
{
    if (!lst._len) return;

    for (T a : lst)
        this->_add(a);
}

template<typename T>
list<T>::~list()
{
    auto end = this->end();
    if (!end._curr) return;

    // get last node
    Node* last_node = _start;
    while (last_node->next) last_node = last_node->next;

    // start rising, clearing data and nodes
    Node* curr = last_node;
    while (curr->prev) {
        delete curr->data;
        curr = curr->prev;
        delete curr->next;
    }

    // erase _start node
    delete _start->data;
    _start->data = nullptr;
}

template<typename T>
list<T>::list(list<T>&& lst)
{
    if (this == &lst)
        throw runtime_error("objects are simular");

    if (!lst._len) return;

    this->_start = lst._start;
    lst._start = nullptr;
}

template<typename T>
list<T>::list(std::initializer_list<T> lst) : list()
{
    for(T elem : lst){
        this->_add(elem);
    }
}

template <typename T>
void list<T>::add_range(const list<T>& lst)
{
    if(!lst._len) return;

    for (T a : lst)
        this->_add(a);
}

template <typename T>
void list<T>::add_range(T* arr, int size)
{
    if(!arr)
        throw invalid_argument("Invalid arr ptr");
    if(size <= 0)
        throw invalid_argument("Size must be > 0");

    for (int i = 0; i < size; i++)
        this->_add(arr[i]);
}

template<typename T>
T list<T>::at(int index) const
{
    return _at(index);
}

template<typename T>
void list<T>::set(int index, const T& elem)
{
    if(index < 0 || index >= _len)
        throw invalid_argument("0 <= index < sizZZZZZe");

    auto iter = this->begin();
    int i = 0;
    while (i++ != index) ++iter;

    *(iter._curr->data) = elem;
}

template<typename T>
T& list<T>::get(int index)
{
    return _get(index);
}

template<typename T>
list<T>& list<T>::operator=(const list& lst)
{
    // get first elem iter of sample
    auto iter = lst.begin();
    Node* curr = _start;
    while (!iter.is_end()) // while next node exists
    {
        // create next node
        try {
            curr->next = new Node(0);
        } catch (bad_alloc&) {
            throw bad_alloc();
        }
        // copy curr data
        *(curr->data) = *(iter._curr->data);

        // move on next node
        curr = curr->next;
        ++iter;
    }
    return *this;
}

template<typename T>
T& list<T>::operator[](int index)
{
    return _get(index);
}

template<typename T>
int list<T>::get_len() const
{
    return _len;
}

template<typename T>
int list<T>::index(const T& elem) const
{
    int i = 0;
    auto iter = this->begin();
    while (!iter.is_end()) {

        if (*iter == elem)
            return i;
        ++iter; ++i;
    }

    return -1;
}

template<typename T>
void list<T>::add(const T& elem)
{
    this->_add(elem);
}

template<typename T>
void list<T>::remove(int index)
{
    if(index < 0 || index >= _len)
        throw invalid_argument("0 <= index < sizZZZZZe");

    auto iter = this->begin();
    int i = 0;
    while (i++ != index) ++iter;

    delete iter._curr->data;
    (iter._curr->prev)->next = (iter._curr->next);
    (iter._curr->next)->prev = (iter._curr->prev);
    delete iter._curr;
}

template<typename T>
void list<T>::sort(int(*comp)(const T& r1, const T& r2))
{
    if (!comp)
        throw invalid_argument("comp is null :((");

    for (Node* crr = _start; crr->next != NULL; crr = crr->next)
    {
        for (Node* nxt = crr->next; nxt != crr; nxt = nxt->next? nxt->next : crr)
        {
            if (comp(*(crr->data), *(nxt->data)) > 0)
            {
                T* tmp = crr->data;
                crr->data = nxt->data;
                nxt->data = tmp;
            }
        }
    }
}

template<typename T>
T* list<T>::to_array()
{
    T* arr = nullptr;
    try {
        arr = new T[_len];
    } catch (bad_alloc&) {
        throw bad_alloc();
    }

    auto iter = this->begin();
    for (int i = 0; !iter.is_end(); i++)
        arr[i] = *iter;

    return arr;
}

template<typename T>
list<T>&& list<T>::combine(const list& lst)
{
    list new_list;
    for (T a : *this)
        new_list._add(a);

    for (T a : lst)
        new_list._add(a);

    return move(new_list);
}

template<typename T>
void list<T>::_add(const T& elem)
{
    // create new node
    Node* new_node;
    try {
        new_node = new Node{};
        new_node->data = new T;
    } catch(bad_alloc&) {
        throw bad_alloc();
    };
    new_node->next = nullptr;
    new_node->data = elem;

    // insert node
    auto iter = this->begin();
    if (!iter._curr) {
        _start = new_node;
        return;
    }
    while (iter._curr->next) ++iter;
    iter._curr->next = new_node;
    new_node->prev = iter._curr;

    ++_len;
}

template<typename T>
T list<T>::_at(int index) const
{
    if(index < 0 || index >= this->get_len())
        throw invalid_argument("Index must be >= 0 and smaller than my display");

    auto iter = this->begin();
    int i = 0;
    while (i++ != index) ++iter;

    return *iter;
}

template<typename T>
T& list<T>::_get(int index)
{
    if(index < 0 || index >= _len)
        throw invalid_argument("0 <= index < sizZZZZZe");

    auto iter = this->begin();
    int i = 0;
    while (i++ != index) ++iter;

    return iter._curr->data;
}

//
// iterator
//
template<typename T>
typename list<T>::iterator list<T>::begin()
{
    return iterator(*this);
}

template<typename T>
typename list<T>::iterator list<T>::end()
{
    iterator iter = this->begin();
    while(!iter.is_end()) ++iter;
    return iter;
}
}
