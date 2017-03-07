#ifndef _GRAPHOP_H
#define _GRAPHOP_H

#include <iostream>
#include "graph.h"

using namespace std;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *
 * BEGIN:   Operations for General Directed Graph
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool adjacent(DG dg, Vertex_ptr x, Vertex_ptr y)
{
    return (dg.edges_find(x, y) != NULL || dg.edges_find(y, x) != NULL);
}

/* add vertex */
void add(DG & dg, Vertex_ptr x)
{
    if (!x) {
        _DEBUG("NULL Vertex_ptr.");
        return;
    }

    dg.vertices_insert(x);
}

/* add edge */
void add_edge(DG & dg, Edge_ptr e, Vertex_ptr from, Vertex_ptr to)
{
    if (!from || !to || !e) {
        _DEBUG("NULL vertices or edge ptr.");
        return;
    }
    if (!e->is_from(from) || !e->is_to(to)) {
        _DEBUG("Input edge does not match input vertices.");
        return;
    }

    dg.edges_from_insert(from, e);
    dg.edges_to_insert(to, e);

    // /* add the edge to graph.edges (both from and to sets) */
    // Graph_edges& ge_from = dg.edges_from();
    // Graph_edges& ge_to = dg.edges_to();

    // auto search = ge_from.find(x);
    // if (search == ge_from.end()) {
    //     _DEBUG("First from_edge for vertex: ", x->to_string());
    //     ge_from.insert(make_pair(x, Set_edges{e}));
    // } else {
    //     search->second.insert(e);
    // }

    // search = ge_to.find(y);
    // if (search == ge_to.end()) {
    //     _DEBUG("First to_edge for vertex: ", y->to_string());
    //     ge_to.insert(make_pair(y, Set_edges{e}));
    // } else {
    //     search->second.insert(e);
    // }

    /* add the vertices to graph.vertices if not exist */
    add(dg, from);
    add(dg, to);
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

/* find edge */
Edge_ptr find_edge(DG & dg, Vertex_ptr from, Vertex_ptr to)
{
    if (!from || !to) {
        _DEBUG("NULL vertices ptr.");
        return NULL;
    }

    Edge_ptr ptr = dg.edges_from_find(from, to);

    // Edge_ptr ptr = NULL;

    // Graph_edges& ge_from = dg.edges_from();
    // auto search_from = ge_from.find(x);
    // if (search_from == ge_from.end()) {
    //     _DEBUG("Graph does not contain vertex: ", x->to_string());
    //     return NULL;
    // } else {
    //     Set_edges& se = search_from->second;
    //     for (auto p : se) {
    //         if (p->to() == y) {
    //             ptr = p;
    //             break;
    //         }
    //     }
    // }

    if (ptr)
        return ptr;

    _DEBUG("There is nothing found in the from set, try the to set.");

    ptr = dg.edges_to_find(from, to);

    // Graph_edges& ge_to = dg.edges_to();
    // auto search_to = ge_to.find(y);
    // if (search_to == ge_to.end()) {
    //     _DEBUG("Graph does not contain vertex: ", y->to_string());
    //     return NULL;
    // } else {
    //     Set_edges& se = search_to->second;
    //     for (auto p : se) {
    //         if (p->from() == x) {
    //             ptr = p;
    //             break;
    //         }
    //     }
    // }

    if (ptr)
        _DEBUG("ABNORMAL ACTIVITY: edge only exists in the edges_to set.");
    return ptr;
}

/* neighbors */
Graph_vertices neighbors_from(DG dg, Vertex_ptr from)
{
    Graph_vertices rv {};

    Graph_edges& ge = dg.edges_from();
    auto search = ge.find(from);
    if (search == ge.end()) {
        _DEBUG("Graph does not contain edges from vertex: ", from->to_string());
        return rv;
    }

    Set_edges& se = search->second;
    for (auto e : se)
        rv.insert(e->to());
    return rv;
}

Graph_vertices neighbors_to(DG dg, Vertex_ptr to)
{
    Graph_vertices rv {};

    Graph_edges& ge = dg.edges_to();
    auto search = ge.find(to);
    if (search == ge.end()) {
        _DEBUG("Graph does not contain edges to vertex: ", to->to_string());
        return rv;
    }

    Set_edges& se = search->second;
    for (auto e : se)
        rv.insert(e->from());
    return rv;
}

Graph_vertices neighbors(DG dg, Vertex_ptr x)
{
    Graph_vertices from = neighbors_from(dg, x);
    Graph_vertices to = neighbors_to(dg, x);

    from.insert(to.begin(), to.end());
    return from;
}

/* remove edge */
Edge_ptr remove_edge(DG & dg, Vertex_ptr from, Vertex_ptr to, Edge_ptr e = NULL)
{
    if (!from || !to) {
        _DEBUG("NULL vertices ptr.");
        return NULL;
    }

    if (!e) {
        /* edge ptr not specified, find it */
        e = find_edge(dg, from, to);
        if (!e)
            return NULL;
    }

    if (!e->is_from(from) || !e->is_to(to)) {
        _DEBUG("Input edge does not match input vertices.");
        return NULL;
    }

    dg.edges_from_erase(from, e);
    dg.edges_to_erase(to, e);

    // /* remove the edge from graph.edges (both from and to sets) */
    // Graph_edges& ge_from = dg.edges_from();
    // Graph_edges& ge_to = dg.edges_to();

    // auto search_from = ge_from.find(x);
    // if (search_from == ge_from.end()) {
    //     _DEBUG("Graph does not contain vertex: ", x->to_string());
    // } else {
    //     Set_edges& se = search_from->second;
    //     auto search = se.find(e);
    //     if (search != se.end())
    //         se.erase(search);
    // }

    // auto search_to = ge_to.find(y);
    // if (search_to == ge_to.end()) {
    //     _DEBUG("Graph does not contain vertex: ", y->to_string());
    // } else {
    //     Set_edges& se = search_to->second;
    //     auto search = se.find(e);
    //     if (search != se.end())
    //         se.erase(search);
    // }

    return e;
}

Edge_ptr remove_edge(DG & dg, Edge_ptr e)
{
    if (!e) {
        _DEBUG("NULL edge ptr.");
        return NULL;
    }

    Vertex_ptr v_from = e->from();
    Vertex_ptr v_to = e->to();
    if (!v_from || !v_to) {
        _DEBUG("NULL vertices.");
        return NULL;
    }

    return remove_edge(dg, v_from, v_to, e);
}

void clear_edges_from(DG & dg, Vertex_ptr from)
{
    if (!from) {
        _DEBUG("NULL vertices.");
        return;
    }

    Graph_vertices set_to = neighbors_from(dg, from);
    for (auto to : set_to)
        dg.edges_erase(from, to);
}

void clear_edges_to(DG & dg, Vertex_ptr to)
{
    if (!to) {
        _DEBUG("NULL vertices.");
        return;
    }

    Graph_vertices set_from = neighbors_to(dg, to);
    for (auto from : set_from)
        dg.edges_erase(from, to);
}

void clear_edges_of(DG & dg, Vertex_ptr x)
{
    clear_edges_from(dg, x);
    clear_edges_to(dg, x);
}

/* remove vertex */
void remove(DG & dg, Vertex_ptr x)
{
    if (!x) {
        _DEBUG("NULL vertices.");
        return;
    }

    clear_edges_of(dg, x);
    dg.vertices_erase(x);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *
 * END:   Operations for General Directed Graph
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif