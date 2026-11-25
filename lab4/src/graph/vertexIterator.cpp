#ifndef VERTEXITERATOR_TPP

#define VERTEXITERATOR_TPP
#include "../../include/graph/vertexIterator.hpp"

template <typename T, bool isConst>
vertexIterator<T, isConst>::vertexIterator() = default;

template <typename T, bool isConst>
vertexIterator<T, isConst>::vertexIterator(vertexIterator<T, isConst>::base_iterator _baseIterator)
    : _iterator(_baseIterator) {}

template <typename T, bool isConst>
typename vertexIterator<T, isConst>::reference vertexIterator<T, isConst>::operator*() const
{
    return this->_iterator->first;
}

template <typename T, bool isConst>
typename vertexIterator<T, isConst>::pointer vertexIterator<T, isConst>::operator->() const
{
    return &(this->_iterator->first);
}

template <typename T, bool isConst>
typename vertexIterator<T, isConst>::base_iterator vertexIterator<T, isConst>::getBaseIterator() const
{
    return this->_iterator;
}

template <typename T, bool isConst>
vertexIterator<T, isConst> &vertexIterator<T, isConst>::operator++()
{
    ++(this->_iterator);
    return *this;
}

template <typename T, bool isConst>
vertexIterator<T, isConst> vertexIterator<T, isConst>::operator++(int)
{
    vertexIterator<T, isConst> temp = *this;
    ++(*this);
    return temp;
}

template <typename T, bool isConst>
vertexIterator<T, isConst> &vertexIterator<T, isConst>::operator--()
{
    --(this->_iterator);
    return *this;
}

template <typename T, bool isConst>
vertexIterator<T, isConst> vertexIterator<T, isConst>::operator--(int)
{
    vertexIterator<T, isConst> temp = *this;
    --(*this);
    return temp;
}

template <typename T, bool isConst>
template <bool otherConst>
bool vertexIterator<T, isConst>::operator==(const vertexIterator<T, otherConst> &other) const
{
    return this->_iterator == other._iterator;
}

template <typename T, bool isConst>
template <bool otherConst>
bool vertexIterator<T, isConst>::operator!=(const vertexIterator<T, otherConst> &other) const
{
    return this->_iterator != other._iterator;
}

#endif