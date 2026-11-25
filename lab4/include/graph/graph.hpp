#ifndef GRAPH_HPP

#define GRAPH_HPP
#include <iostream>
#include <map>
#include <set>

template <typename T>
class graph
{
public:
    using vertex = T;
    using edge = std::pair<vertex, vertex>;
    using neighbors = std::set<vertex>;

    graph() = default;
    graph(const graph &);

    bool empty() const;
    void clear();

    graph &operator=(const graph &);
    bool operator==(const graph &) const;
    bool operator!=(const graph &) const;
    bool operator<(const graph &) const;
    bool operator>(const graph &) const;
    bool operator<=(const graph &) const;
    bool operator>=(const graph &) const;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const graph<U> &);

    void addVertex(const vertex &);
    void addEdge(const edge &);
    void removeVertex(const vertex &);
    void removeEdge(const edge &);
    bool containsVertex(const vertex &) const;
    bool containsEdge(const edge &) const;
    size_t getAmountVertex() const;
    size_t getAmountEdge() const;
    size_t getVertexDegree(const vertex &) const;

    /* iterator begin();
     iterator end();
     constIterator begin() const;
     constIterator end() const;
 */
private:
    std::map<vertex, neighbors> _graph;
};

#endif