#ifndef _GRAPHOP_H
#define _GRAPHOP_H

#include <iostream>
#include "graph.h"

using namespace std;

// template<Vertex V>
// int fun(Vertex v) { return v.value().second; }

bool adjacent(DG dg, Vertex_ptr x, Vertex_ptr y);
Graph_vertices neighbors(DG dg, Vertex_ptr x);

/* add vertex */
void add(DG & dg, Vertex_ptr x)
{
    if (!x) {
        _DEBUG("NULL Vertex_ptr.");
        return;
    }

    Graph_vertices& gv = dg.vertices();
    gv.insert(x);
}

/* add edge */
void add_edge(DG & dg, Edge_ptr e, Vertex_ptr x, Vertex_ptr y)
{
    if (!x || !y || !e) {
        _DEBUG("NULL vertices or edge ptr.");
        return;
    }
    if (!e->contain(x) || !e->contain(y)) {
        _DEBUG("Input edge does not contain input vertices.");
        return;
    }

    /* add the edge to graph.edges (both from and to sets) */
    Graph_edges& ge_from = dg.edges_from();
    Graph_edges& ge_to = dg.edges_to();

    auto search_from = ge_from.find(x);
    if (search_from == ge_from.end()) {
        _DEBUG("First from_edge for vertex: ", x->to_string());
        ge_from.insert(make_pair(x, Set_edges{e}));
    } else {
        search_from->second.insert(e);
    }

    auto search_to = ge_to.find(y);
    if (search_to == ge_to.end()) {
        _DEBUG("First to_edge for vertex: ", y->to_string());
        ge_to.insert(make_pair(y, Set_edges{e}));
    } else {
        search_to->second.insert(e);
    }

    /* add the vertices to graph.vertices if not exist */
    add(dg, x);
    add(dg, y);
}

void add_edge(DG & dg, Edge_ptr e)
{
    if (!e) {
        _DEBUG("NULL Edge_ptr.");
        return;
    }

    Vertex_ptr v_from = e->from();
    Vertex_ptr v_to = e->to();
    if (!v_from || !v_to) {
        _DEBUG("NULL vertices.");
        return;
    }

    add_edge(dg, e, v_from, v_to);
}

template<typename T>
Edge_ptr add_edge(DG & dg, Vertex_ptr x, Vertex_ptr y, T val)
{
    if (!x || !y) {
        _DEBUG("NULL vertices.");
        return NULL;
    }

    Edge_ptr e(new directed_edge(x, y, val));
    add_edge(dg, e, x, y);
    return e;
}

#endif