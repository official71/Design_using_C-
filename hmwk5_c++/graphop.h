#ifndef _GRAPHOP_H
#define _GRAPHOP_H

#include <iostream>
#include "dg.h"
#include "dag.h"
#include "dt.h"

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
Retval add(DG & dg, Vertex_ptr x)
{
    if (!x) {
        _DEBUG("NULL Vertex_ptr.");
        return Failure;
    }

    dg.vertices_insert(x);
    return Success;
}

/* add edge */
Retval add_edge(DG & dg, Edge_ptr e, Vertex_ptr from, Vertex_ptr to)
{
    _DEBUG("DG version...");

    if (!from || !to || !e) {
        _DEBUG("NULL vertices or edge ptr.");
        return Failure;
    }
    if (!e->is_from(from) || !e->is_to(to)) {
        _DEBUG("Input edge does not match input vertices.");
        return Failure;
    }

    dg.edges_from_insert(from, e);
    dg.edges_to_insert(to, e);

    /* add the vertices to graph.vertices if not exist */
    add(dg, from);
    add(dg, to);

    return Success;
}

Retval add_edge(DG & dg, Edge_ptr e)
{
    if (!e) {
        _DEBUG("NULL Edge_ptr.");
        return Failure;
    }

    Vertex_ptr v_from = e->from();
    Vertex_ptr v_to = e->to();
    if (!v_from || !v_to) {
        _DEBUG("NULL vertices.");
        return Failure;
    }

    return add_edge(dg, e, v_from, v_to);
}

template<typename T>
Edge_ptr add_edge(DG & dg, Vertex_ptr from, Vertex_ptr to, T val)
{
    if (!from || !to) {
        _DEBUG("NULL vertices.");
        return NULL;
    }

    Edge_ptr e(new directed_edge(from, to, val));
    if (add_edge(dg, e, from, to) == Failure)
        return NULL;
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
    if (ptr)
        return ptr;

    _DEBUG("There is nothing found in the from set, try the to set.");

    ptr = dg.edges_to_find(from, to);
    if (ptr)
        _DEBUG("ABNORMAL ACTIVITY: edge only exists in the edges_to set.");
    return ptr;
}

/* neighbors */
Graph_vertices neighbors_from(DG dg, Vertex_ptr from)
{
    Graph_vertices rv {};
    if (!from) {
        _DEBUG("NULL vertices.");
        return rv;
    }
    return dg.edges_from_neighbors(from);
}

Graph_vertices neighbors_to(DG dg, Vertex_ptr to)
{
    Graph_vertices rv {};
    if (!to) {
        _DEBUG("NULL vertices.");
        return rv;
    }
    return dg.edges_to_neighbors(to);
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
 *-------------------------------------------------------------------
 *
 * BEGIN: Operations for Directed Acyclic Graph
 *        (All operations that changes the underlying graph must be
 *         validated against cycles)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


Retval add_edge(DAG & dag, Edge_ptr e, Vertex_ptr from, Vertex_ptr to)
{
    _DEBUG("DAG version...");

    if (!from || !to || !e) {
        _DEBUG("NULL vertices or edge ptr.");
        return Failure;
    }
    if (!e->is_from(from) || !e->is_to(to)) {
        _DEBUG("Input edge does not match input vertices.");
        return Failure;
    }

    /* construct a temporary graph to check cyclicity */
    directed_acyclic_graph tmp_dag(dag.base());
    tmp_dag.edges_from_insert(from, e);
    tmp_dag.edges_to_insert(to, e);
    tmp_dag.vertices_insert(from);
    tmp_dag.vertices_insert(to);

    if (tmp_dag.is_cyclic()) {
        _DEBUG("ERROR: edge ", e->to_string(), " causes cycle to DAG.");
        return Failure;
    }

    dag.copy_base(tmp_dag.base(), true);
    return Success;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *
 * END:   Operations for Directed Acyclic Graph
 *
 *-------------------------------------------------------------------
 *
 * BEGIN: Operations for Directed Tree
 *        1. Adding a single vertex/node is not allowed (DT must be connected)
 *        2. Adding a single edge is allowed iff the edge connnects an existing 
 *           node and a new leaf node
 *        3. Removing a single edge is not allowed
 *        4. Removing a single node is allowed iff it is a leaf node, and the 
 *           edge that links to it will be removed too
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Retval add(DT & dt, Vertex_ptr x)
{
    _DEBUG("DT does not allow adding a node without an edge from its parent.");
    return Failure;
}

Retval add_edge(DT & dt, Edge_ptr e, Vertex_ptr from, Vertex_ptr to)
{
    _DEBUG("DG version...");

    if (!from || !to || !e) {
        _DEBUG("NULL vertices or edge ptr.");
        return Failure;
    }
    if (!e->is_from(from) || !e->is_to(to)) {
        _DEBUG("Input edge does not match input vertices.");
        return Failure;
    }

    if (!dt.has_vertex(from)) {
        _DEBUG("The vertex: ", from->to_string(), \
            " does not exist in DT, no edges from it shall be added.");
        return Failure;
    }
    if (dt.has_vertex(to)) {
        _DEBUG("The vertex: ", to->to_string(), \
            " already exists in DT, no edges to it shall be added.");
        return Failure;
    }

    dt.edges_from_insert(from, e);
    dt.edges_to_insert(to, e);
    dt.vertices_insert(to);

    return Success;
}

//TODO remove

#endif