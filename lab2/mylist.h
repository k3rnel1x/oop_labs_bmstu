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
    mylist();
    mylist(const mylist<T>& lst);
    explicit mylist(std::initializer_list<T> lst);
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

        // Methods
        // iterator next();
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


// ********************** list ********************** //

template<typename T>
mylist<T>::mylist()
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
    if (sample.get_len() == 0)
        return;
    try {
        _start = new Node;
        _start->data = new T;
    } catch(bad_alloc&) {
        throw bad_alloc();
    };
    Node* curr = _start;
    *(curr->data) = sample.at(0);
    for(int i = 1; i < sample.get_len(); i++){
        Node* new_node;
        try {
            new_node = new Node;
            new_node->data = new T;
        } catch(bad_alloc&) {
            throw bad_alloc();
        };
        new_node->next = NULL;

        // copy data from lst
        *(new_node->data) = sample.at(i);

        // set new node to last
        curr->next = new_node;
        new_node->prev = curr;
        curr = new_node;
    }
}

template<typename T>
mylist<T>::mylist(mylist<T>&& sample)
{
    if (this == &sample)
        throw runtime_error("objects are simular");

    Node* sample_curr = sample._start;
    Node* curr = _start;
    while (sample_curr->next)
    {
        // create next node
        try {
            curr->next = new Node;
        } catch (bad_alloc&) {
            throw bad_alloc();
        }
        // copy sample curr data ptr
        curr->data = sample_curr->data;
        sample_curr->data = NULL;
        // move on next node
        curr = curr->next;
        sample_curr = sample_curr->next;
    }
}

template<typename T>
my::mylist<T>::mylist(std::initializer_list<T> lst) : mylist()
{
	for(T elem : lst){
		this->add(elem);
	}
}

template <typename T>
void my::mylist<T>::add_range(const mylist<T>& lst)
{
	if(!lst.get_len())
		return;
	Node* last_node = _start;
	while(last_node->next) last_node = last_node->next;
    if (last_node == _start)
        *(last_node->data) = lst.at(0);

	for(int i = (last_node == _start); i < lst.get_len(); i++){
		Node* new_node; 
		try {
			new_node = new Node;
			new_node->data = new T;
		} catch(bad_alloc&) {
			throw bad_alloc();	
		};
		new_node->next = NULL;

		// copy data from lst
		*(new_node->data) = lst.at(i);

		// set new node to last 
		last_node->next = new_node;
		new_node->prev = last_node;					
		last_node = new_node;
	}
}

template <typename T> 
void my::mylist<T>::add_range(T* arr, int size)
{
	if(!arr)
		throw invalid_argument("Invalid arr ptr");
	if(size <= 0)
		throw invalid_argument("Size must be > 0");

	Node* last_node = _start;
	while(last_node->next) last_node = last_node->next;

	for(int i = 0; i < size; i++){
		Node* new_node; 
		try {
			new_node = new Node;
			new_node->data = new T;
		} catch(bad_alloc&) {
			throw bad_alloc();	
		};
		new_node->next = NULL;

		// copy data from lst
		*(new_node->data) = arr[i];
		// set new node to last 
		last_node->next = new_node;
		new_node->prev  = last_node;					
		last_node = new_node;
	}
	
}

template<typename T>
T mylist<T>::at(int index) const 
{
	if(index < 0)
		throw invalid_argument("Index must be >= 0");

	Node* curr = _start;
	for(int i = 0; curr->next != NULL && i < index; ++i) {
		curr = curr->next;
	}

	return *(curr->data);
}

template<typename T>
void mylist<T>::set_elem(int index, const T& elem)
{
    if(index < 0 || index >= this->get_len())
        throw invalid_argument("0 <= index < size");

    Node* curr = _start;
    for (int i = 0; i != index; i++)
        curr = curr->next;

    *(curr->data) = elem;
}

template<typename T>
typename my::mylist<T>::iterator my::mylist<T>::begin()
{
    return my::mylist<T>::iterator(*this);
}


template<typename T>
typename my::mylist<T>::iterator my::mylist<T>::end() 
{
	auto iter = this->begin();
	while(!iter.is_end()) ++iter;
	return ++iter;
}

template<typename T>
void mylist<T>::swap_nodes(Node** _start, Node* a, Node* b)
{
    // TODO !!!!!!!
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
        } catch (bad_alloc&) {
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
        } catch (bad_alloc&) {
            throw bad_alloc();
        }
        *(_start->data) = elem;
        _start->next = NULL;
        _start->prev = NULL;
        return;
    }

    // if one or more exist create next node
    // alloc new node and data
    Node* new_node;
    try {
        new_node = new Node;
        new_node->data = new T;
    } catch (bad_alloc&) {
        throw bad_alloc();
    }

    // copy data no new node
    *(new_node->data) = elem;

    // insert new node
    Node* end_node = _start;
    while (end_node->next) end_node = end_node->next;
    end_node->next = new_node;
	new_node->prev = end_node;
}

template<typename T>
T& my::mylist<T>::get_elem(int index)
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
void mylist<T>::remove_elem(int index)
{
    if(index < 0 || index >= this->get_len())
        throw invalid_argument("0 <= index < size");

    Node* curr = _start;
    for (int i = 0; i != index; i++)
        curr = curr->next;

    if (curr == _start)
        _start = curr->next;
    else
    {
        (curr->prev)->next = curr->next;
        (curr->next)->prev = curr->prev;
    }


    delete curr->data;
    delete curr;
}

template<typename T>
void mylist<T>::sort(int(*comp)(const T& r1, const T& r2))
{
    if (!comp)
        throw invalid_argument("comp is null :((");

    for (Node* crr = _start; (crr->next)->next != NULL; crr = crr->next)
    {
        for (Node* nxt = crr->next; nxt->next != NULL; nxt = nxt->next)
        {
            if (comp(*(crr->data), *(nxt->data)) > 0);
                // swap_nodes(&_start, crr, nxt);
        }
    }
}

template<typename T>
T* mylist<T>::to_array()
{
    T* arr = NULL;
    try {
        arr = new T[this->get_len()];
    } catch (bad_alloc&) {
        throw bad_alloc();
    }
    Node* curr = _start;
    for (int i = 0; i < this->get_len(); i++, curr = curr->next)
        arr[i] = *(curr->data);

    return arr;
}

template<typename T>
mylist<T> mylist<T>::combine(const mylist<T>& lst)
{
    mylist<T> new_list;
    new_list.add_range(lst);
    return new_list;
}


// ********************** iterator ********************** //
template <typename T>
mylist<T>::iterator::iterator(mylist<T>& lst)
{
	this->_curr = lst._start;
}

template <typename T>
T& mylist<T>::iterator::operator*()
{
	return *(_curr->data);
}

template <typename T>
typename mylist<T>::iterator& mylist<T>::iterator::operator++()
{
	_curr = _curr->next;
	return *this;
}

template <typename T>
bool mylist<T>::iterator::operator!=(iterator& b)
{
	return this->_curr != b._curr;
}
	
template <typename T>
bool mylist<T>::iterator::is_end()
{
	return !(this->_curr->next);
}

template <typename T>
T mylist<T>::iterator::value()
{
	return *(_curr->data);
}

}

#endif //LIST_H
