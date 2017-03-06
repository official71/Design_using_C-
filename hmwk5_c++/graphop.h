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
    Graph_vertices& sv = dg.vertices();
    sv.insert(x);
}

#endif