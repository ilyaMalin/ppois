#ifndef VERTEXITERATOR_HPP

#define VERTEXITERATOR_HPP
#include <cstddef>
#include <iterator>
#include <map>
#include <set>
#include <type_traits>

template <typename T, bool isConst = false>
class vertexIterator
{
public:
    using container_type = std::map<T, std::set<T>>;

    using base_iterator = std::conditional_t<isConst, typename container_type::const_iterator, typename container_type::iterator>;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;

    vertexIterator();
    explicit vertexIterator(base_iterator);

    reference operator*() const;
    pointer operator->() const;

    vertexIterator &operator++();
    vertexIterator operator++(int);
    vertexIterator &operator--();
    vertexIterator operator--(int);

    template <bool otherConst>
    bool operator==(const vertexIterator<T, otherConst> &) const;

    template <bool otherConst>
    bool operator!=(const vertexIterator<T, otherConst> &) const;

    base_iterator getBaseIterator() const;

private:
    template <typename, bool>
    friend class vertexIterator;

    base_iterator _iterator;
};

#include "../../src/graph/vertexIterator.cpp"

#endif
