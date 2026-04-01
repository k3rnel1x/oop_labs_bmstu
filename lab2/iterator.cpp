#include "list.h"
//
// Created by k3rnel1x on 01.04.2026.
//
// ********************** iterator ********************** //
namespace my {
//
// public
//

template <typename T>
list<T>::iterator::iterator(list<T>& lst)
{
    this->_curr = lst._start;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::next()
{
    return _next();
}

template <typename T>
bool list<T>::iterator::is_end()
{
    return !this->_curr;
}

template <typename T>
T list<T>::iterator::value()
{
    return _value();
}

//
// protected
//

template<typename T>
typename list<T>::iterator list<T>::iterator::_next()
{
    // if (!_curr)
        // throw runtime_error("_curr is null");

    _curr = _curr->next;
    return *this;
}

template <typename T>
T list<T>::iterator::_value()
{
    // if (!_curr->data)
        // throw runtime_error("data is null");
    return *(_curr->data);
}

template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++()
{
    return _next();
}

template <typename T>
T& list<T>::iterator::operator*()
{
    return *(_curr->data);
}

template <typename T>
bool list<T>::iterator::operator!=(iterator& b)
{
    return this->_curr != b._curr;
}
}