#ifndef _GRAPH_H
#define _GRAPH_H

#include <string>
#include <utility>
#include <memory>
#include "concepts.h"

using namespace std;

typedef pair<string,int> Val;

struct vertex {
    Val val;
    
    vertex(void) { val = make_pair("NULL", -1); }
    vertex(Val v) { val = v; }

    Val value(void) { return val; }
    void set_value(Val v) { val = v; }

    string to_string(void) {
        return "[(" + get<0>(val) + ")::(" + std::to_string(get<1>(val)) + ")]";
    }
};
typedef shared_ptr<vertex> vertex_ptr;

struct directed_edge {
    Val val;
    vertex_ptr v_from, v_to;

    directed_edge(void) {
        val = make_pair("NULL-->NULL", -1);
    }
    directed_edge(vertex_ptr from, vertex_ptr to, int v=-1) {
        v_from = from;
        v_to = to;
        val = make_pair(from->to_string() + "-->" + to->to_string(), v);
    }
    directed_edge(vertex_ptr from, vertex_ptr to, Val v) {
        v_from = from;
        v_to = to;
        val = v;
    }

    bool contain(vertex_ptr vp) { return v_from == vp || v_to == vp; }
    bool is_from(vertex_ptr vp) { return v_from == vp; }
    bool is_to(vertex_ptr vp) { return v_to == vp; }

    vertex_ptr from(void) { return v_from; }
    vertex_ptr to(void) { return v_to; }

    Val value(void) { return val; }
    void set_value(Val v) { val = v; }

    string to_string(void) {
        return "{(" + get<0>(val) + ")::(" + std::to_string(get<1>(val)) + ")}";
    }
};
typedef shared_ptr<directed_edge> edge_ptr;

#endif