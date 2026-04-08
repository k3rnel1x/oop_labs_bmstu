#include "list.h"

namespace my {
template<typename T>
typename list<T>::iterator& list<T>::iterator::operator=(iterator&& iter)
{
    this->current_node = iter.current_node;
    iter.current_node = nullptr;

    return *this;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::next()
{
    iterator iter = *this;
    return ++iter;
}

template<typename T>
T list<T>::iterator::value()
{
    if (!current_node)
        throw invalid_argument("iterator is empty");

    return T(current_node->val);
}

template<typename T>
bool list<T>::iterator::is_end() const { return !current_node; }

template<typename T>
typename list<T>::iterator& list<T>::iterator::operator++()
{
    if (!current_node)
        throw invalid_argument("trying to increment empty iterator");

    if (!current_node->next)
        throw invalid_argument("trying increment out of range");

    current_node = current_node->next;
    return *this;
}

template<typename T>
typename list<T>::iterator & list<T>::iterator::operator--()
{
    if (!current_node)
        throw invalid_argument("trying to decrement empty iterator");

    if (!current_node->prev)
        throw invalid_argument("trying decrement out of range");

    current_node = current_node->prev;
    return *this;
}

template<typename T>
T& list<T>::iterator::operator*()
{
    if (!current_node)
        throw invalid_argument("iterator is empty");

    return current_node->val;
}

template<typename T>
bool list<T>::iterator::operator==(iterator& b) const
{
    return current_node == b.current_node;
}

template<typename T>
bool list<T>::iterator::operator!=(const iterator& b) const
{
    return current_node != b.current_node;
}

template<typename T>
bool list<T>::iterator::operator!=(const iterator&& b) const
{
    return current_node != b.current_node;
}

// template<typename T>
// typename list<T>::iterator&& list<T>::iterator::operator-(int a)
// {
//     iterator tmp{*this};
//     for (int i = 0; i < a; ++i) {
//         // if (!tmp.current_node->prev && i < a - 1)
//             // throw std::out_of_range("trying to out of range");
//         --tmp;
//     }
//
//     return std::move(tmp);
// }
//
// template<typename T>
// typename list<T>::iterator&& list<T>::iterator::operator+(int a)
// {
//     iterator tmp{current_node};
//     for (int i = 0; i < a; ++i) {
//         if (!tmp.current_node->prev && i < a - 1)
//             throw std::out_of_range("trying to out of range");
//         ++tmp;
//     }
//
//     return std::move(tmp);
// }

}
