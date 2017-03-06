#ifndef _CONCEPTS_H
#define _CONCEPTS_H


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