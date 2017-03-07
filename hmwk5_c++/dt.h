#ifndef _DT_H
#define _DT_H

#include <string>
#include <utility>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include "concepts.h"
#include "basic.h"
#include "dfs.h"

using namespace std;

struct directed_tree
{
    base_graph bg;
    Vertex_ptr root_node = NULL;

    Graph_vertices& vertices() { return bg.vertices; }
    Graph_edges& edges_from() { return bg.edges_from; }
    Graph_edges& edges_to() { return bg.edges_to; }

    Vertex_ptr root() { return root_node; }
    void set_root(Vertex_ptr vp) { root_node = vp; }
    bool has_root() { return root_node != NULL; }

    string to_string() 
    {
        return "\nTYPE: Directed Tree" \
         "\nVERTICES:\n" + bg.vertices_to_string() + \
         "\nEDGES:\n" + bg.edges_to_string(edges_from());
    }
};

#endif