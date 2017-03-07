#ifndef _CONCEPTS_H
#define _CONCEPTS_H

#include <type_traits>

template<typename T> using Value_type = typename T::value_type;
template<typename T> using Iterator_of = typename T::iterator;

template<typename T, typename U>
concept bool Same_type = std::is_same<T, U>::value;

template<typename T>
concept bool Sequence = requires(T t) {
    typename Value_type<T>;
    typename Iterator_of<T>;

    { begin(t) } -> Iterator_of<T>;
    { end(t) } -> Iterator_of<T>;
    requires Same_type<Value_type<T>, Value_type<Iterator_of<T>>>;
};

template<typename V>
concept bool Vertex = requires(V v) {
    v.value();
    { v.to_string() } -> std::string;
};

template<typename E>
concept bool DirectedEdge = requires(E e) {
    e.from();
    e.to();
    e.value();
    { e.to_string() } -> std::string;
};

template<typename G>
concept bool DG = requires(G g) {
    { g.to_string() } -> std::string;    
};

template<typename G>
concept bool DAG = requires(G g) {
    { g.to_string() } -> std::string;
    g.topological_order();
};

template<typename G>
concept bool DT = requires(G g) {
    { g.to_string() } -> std::string;
    g.root();
};

#endif