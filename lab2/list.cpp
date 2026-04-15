#include "list.h"

#include <algorithm>

namespace my {
template<typename T>
list<T>::list()
{
    start_node = end_node = new Node{};

    // iters set to one node
    start_iterator = iterator(start_node);
    end_iterator   = iterator(end_node);
}

template<typename T>
list<T>::list(const list& lst) : list()
{
    for (auto iter = lst.start_iterator; iter != lst.end_iterator; ++iter)
        this->append(T(*iter));
}

template<typename T>
list<T>::list(std::initializer_list<T> init_lst) : list()
{
    for (T val : init_lst) {
        this->append(val);
    }

    this->len = init_lst.size();
}

template<typename T>
list<T>::list(list&& lst)
{
    // if (!lst.get_len()) return;

    start_node   = lst.start_node;
    end_node     = lst.end_node;
    lst.end_node = lst.start_node = nullptr;


    start_iterator   = lst.start_iterator;
    end_iterator     = lst.end_iterator;
    lst.end_iterator = lst.start_iterator = iterator(nullptr);

    len = lst.len;
    lst.len = 0;
}

template<typename T>
list<T>::~list()
{
    if (!len) {
        delete start_node;
        return;
    }

    for (auto iter = iterator(end_node->prev); iter != start_iterator; --iter)
    {
        delete iter.current_node->next;
    }

    delete start_node;
    start_node = nullptr;
    end_node = nullptr;
    start_iterator = iterator(nullptr);
    end_iterator   = iterator(nullptr);
}

template<typename T>
int list<T>::get_len() const { return int(len); }

template<typename T>
int list<T>::indexof(const T& elem) const
{
    int idx = 0;
    for (auto iter = start_iterator; iter != end_iterator; ++iter, ++idx)
        if (elem == *iter)
            return idx;

    return -1;
}

template<typename T>
void list<T>::add(const T &elem) { this->append(elem); }

template<typename T>
void list<T>::add_range(const list& b)
{
    for (auto iter = b.start_iterator; iter != iterator(b.end_iterator); ++iter) // костыль
        this->append(T(*iter));
}

template<typename T>
void list<T>::add_range(T* arr, int size)
{
    for (size_t i = 0; i < size; ++i)
        this->append(arr[i]);
}

template<typename T>
inline T& list<T>::at(int index) { return on_index(index); }

template<typename T>
void list<T>::set(int index, const T& elem)
{
    if (index < 0 || index >= len)
        throw std::invalid_argument("index out of range");

    int i = 0;
    for (auto iter = start_iterator; i != index; ++iter, ++i)
        if (i == index) {
            *iter = elem;
            return;
        }
}

template<typename T>
T list<T>::get(int index) const // костыль
{
    if (index < 0 || index >= len)
        throw std::invalid_argument("index out of range");

    int i = 0;
    auto iter = start_iterator;
    for (; i != index; ++iter, ++i)
        if (i == index)
            break;

    return T(*iter);
}

template<typename T>
void list<T>::remove(int index)
{
    if (index < 0 || index >= len)
        throw std::invalid_argument("index out of range");

    int i = 0;
    for (auto iter = start_iterator; i != index; ++iter, ++i)
        if (i == index) {
            iter_deleter(iter);
            return;
        }
}

template<typename T>
void list<T>::remove(iterator& iter) { iter_deleter(iter); }

template<typename T>
T* list<T>::to_array()
{
    T* arr = new T[len]{};
    size_t i = 0;
    for (auto iter = start_iterator; iter != end_iterator; ++iter)
        arr[i++] = *iter;

    return arr;
}

template<typename T>
void list<T>::sort(int(*comp)(const T& r1, const T& r2))
{
    if (len < 2 || !comp) return;

    for (auto iter_a = start_iterator; iter_a != iterator(end_iterator.current_node->prev); ++iter_a)
    {
        for (auto iter_b = iterator(iter_a.current_node->next); iter_b != end_iterator; ++iter_b) {
            if (comp(*iter_b, *iter_a) > 0)
                swap_iters(iter_a, iter_b);
        }
    }

}

template<typename T>
typename list<T>::iterator list<T>::begin() { return iterator(this->start_iterator); }

template<typename T>
typename list<T>::iterator list<T>::end() { return iterator(this->end_iterator); }

template<typename T>
void list<T>::append(const T& val)
{
    Node* node = new Node{val};
    node->val = val;

    if (!len) {
        start_node->prev = node;
        node->next = start_node;
        start_node = node;
        start_iterator.current_node = node;

    } else {
        (end_node->prev)->next = node;
        node->prev = (end_node->prev);
        end_node->prev = node;
        node->next = end_node;
        // end_iterator = iterator(end_node);
    }

    ++len;
}

template<typename T>
void list<T>::append(T&& val)
{
    Node* node = new Node{val};

    if (!len) {
        start_node->prev = node;
        node->next = start_node;
        start_node = node;
        start_iterator.current_node = node;

    } else {
        (end_node->prev)->next = node;
        node->prev = (end_node->prev);
        end_node->prev = node;
        node->next = end_node;
        // end_iterator = iterator(end_node);
    }

    ++len;
}

template<typename T>
inline void list<T>::swap_iters(iterator& iter1, iterator& iter2)
{
    T tmp {*iter1};
    *iter1 = std::move(*iter2);
    *iter2 = std::move(tmp);
}

template<typename T>
T& list<T>::on_index(int index)
{
    if (index < 0 || index >= len)
        throw std::invalid_argument("index out of range");

    int i = 0;
    auto iter = start_iterator;
    for (; iter != end_iterator; ++iter)
        if (i++ == index)
            break;

    return *iter;
}

template<typename T>
list<T> list<T>::unit(const list& lst)
{
    list<T> tmp{*this};

    for (auto iter = lst.start_iterator; iter != lst.end_iterator; ++iter)
        tmp.append(T(*iter));

    return tmp;
}

template<typename T>
list<T>& list<T>::operator=(const list& lst)
{
    auto target = lst.start_iterator;
    auto iter   = start_iterator;
    for (; target != lst.end_iterator; ++iter, ++target)
        if (iter == end_iterator)
        {
            this->append(T(target.current_node->val));
            iter.current_node = iter.current_node->prev;
        }
        else
            *iter = T(target.current_node->val);

    if (iter != end_iterator)
        for (auto itr = iterator(end_node->prev); itr != iter; --itr)
            iter_deleter(itr);

    return *this;
}

template<typename T>
bool list<T>::operator==(const list& lst) const
{
    if (&lst == this) return true;
    if (len != lst.len) return false;

    auto iter = start_iterator;
    auto iter_lst = lst.start_iterator;
    for (; iter != end_iterator && iter_lst != lst.end_iterator; ++iter, ++iter_lst)
        if (*iter != *iter_lst)
            return false;

    return true;
}

template<typename T>
T& list<T>::operator[](int index) { return on_index(index); }

template<typename T>
void list<T>::iter_deleter(iterator& del_iter)
{
    for (auto iter = start_iterator; iter != end_iterator; ++iter) {
        if (iter == del_iter) {
            (iter.current_node->prev)->next = iter.current_node->next;
            (iter.current_node->next)->prev = iter.current_node->prev;

            delete iter.current_node;
            del_iter.current_node = nullptr;
            --len;
            return;
        }
    }

    throw std::invalid_argument("iterator does not exist");
}
}
