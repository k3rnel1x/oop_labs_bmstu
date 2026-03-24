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
    // list(list<T>&& list);
    explicit mylist(std::initializer_list<T> lst);
    ~mylist();

    // Methods
    int  get_len() 				  const;
    int  get_index(const T& elem) const;
    void add(const T& elem);
    void add_range(const mylist<T>& b);
    void add_range(T* arr, int size);
    T at(int index) const;
    // void set_elem(int index,const T& elem);
    T&   get_elem(int index);
    // void remove_elem(int index);
    // void sort(int (*comp)(const T& r1, const T& r2));
    // T*   to_array();
    // list<T> combine(const list<T>& lst);


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

	for(int i = 0; i < lst.get_len(); i++){
		Node* new_node; 
		try {
			new_node = new Node;
			new_node->data = new T;
		} catch(bad_alloc) {
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
		} catch(bad_alloc) {
			throw bad_alloc();	
		};
		new_node->next = NULL;
		cout << i << endl;
		cout << arr[i] << endl;

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
typename my::mylist<T>::iterator my::mylist<T>::begin()
{
    return my::mylist<T>::iterator(*this);
}


template<typename T>
typename my::mylist<T>::iterator my::mylist<T>::end() 
{
	auto iter = this->begin();
	while(!iter.is_end()) ++iter;
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

    // if one or more exist create next node
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
	new_node->prev = end_node;
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
	return !this->_curr->next;
}

template <typename T>
T mylist<T>::iterator::value()
{
	return *(_curr->data);
}

}

#endif //LIST_H
