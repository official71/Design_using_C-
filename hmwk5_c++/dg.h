#ifndef _DG_H
#define _DG_H

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

struct directed_graph 
{
    base_graph bg;

    directed_graph() {}
    directed_graph(base_graph& base): bg(base) {}
    directed_graph(vector<Vertex_ptr>& vv);
    directed_graph(vector<Edge_ptr>& ve);
    directed_graph(vector<Vertex_ptr>& vv, vector<Edge_ptr>& ve);

    void copy_base(base_graph& base) { bg = base; }

    base_graph& base() { return bg; }
    Graph_vertices& vertices() { return bg.vertices; }
    Graph_edges& edges_from() { return bg.edges_from; }
    Graph_edges& edges_to() { return bg.edges_to; }

    bool has_vertex(Vertex_ptr v) { return bg.vertex_in_graph(v); }
    bool has_edge(Edge_ptr e) { return bg.edge_in_graph(e); }

    void vertices_insert(Vertex_ptr v) { bg.vertices_insert(v); }
    void vertices_erase(Vertex_ptr v) { bg.vertices_erase(v); }

    void edges_from_insert(Vertex_ptr f, Edge_ptr e) { bg.edges_from_insert(f, e); }
    void edges_to_insert(Vertex_ptr t, Edge_ptr e) { bg.edges_to_insert(t, e); }

    Edge_ptr edges_from_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_from_find(f, t); }
    Edge_ptr edges_to_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_to_find(f, t); }
    Edge_ptr edges_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_from_find(f, t); }

    Graph_vertices edges_from_neighbors(Vertex_ptr f) { return bg.edges_from_neighbors(f); }
    Graph_vertices edges_to_neighbors(Vertex_ptr t) { return bg.edges_to_neighbors(t); }

    void edges_from_erase(Vertex_ptr f, Edge_ptr e) { bg.edges_from_erase(f, e); }
    void edges_to_erase(Vertex_ptr t, Edge_ptr e) { bg.edges_to_erase(t, e); }
    void edges_erase(Vertex_ptr f, Vertex_ptr t) { bg.edges_from_to_erase(f, t); }

    bool is_cyclic()
    {
        depth_first_search DFS(bg);
        return DFS.dfs(true);
    }

    string to_string() 
    {
        return "\nTYPE: Directed Graph" \
         "\nVERTICES:\n" + bg.vertices_to_string() + \
         "\nEDGES:\n" + bg.edges_to_string(edges_from());
    }
};

directed_graph::directed_graph(vector<Vertex_ptr>& vv) { bg = base_graph(vv); }

directed_graph::directed_graph(vector<Edge_ptr>& ve) { bg = base_graph(ve); }

directed_graph::directed_graph(vector<Vertex_ptr>& vv, vector<Edge_ptr>& ve) 
{
    bg = base_graph(vv, ve);
}


#endif