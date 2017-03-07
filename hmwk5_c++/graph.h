#ifndef _GRAPH_H
#define _GRAPH_H

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
    directed_graph(base_graph& base): bg(base)
    {
        _DEBUG("<directed_graph> constructor using base_graph&");
    }

    void copy_base(base_graph& base)
    {
        bg = base;
    }

    base_graph& base() { return bg; }
    Graph_vertices& vertices() { return bg.vertices; }
    Graph_edges& edges_from() { return bg.edges_from; }
    Graph_edges& edges_to() { return bg.edges_to; }

    void vertices_insert(Vertex_ptr v) { bg.vertices_insert(v); }
    void vertices_erase(Vertex_ptr v) { bg.vertices_erase(v); }

    void edges_from_insert(Vertex_ptr f, Edge_ptr e) { bg.edges_from_insert(f, e); }
    void edges_to_insert(Vertex_ptr t, Edge_ptr e) { bg.edges_to_insert(t, e); }

    Edge_ptr edges_from_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_from_find(f, t); }
    Edge_ptr edges_to_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_to_find(f, t); }
    Edge_ptr edges_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_from_find(f, t); }

    void edges_from_erase(Vertex_ptr f, Edge_ptr e) { bg.edges_from_erase(f, e); }
    void edges_to_erase(Vertex_ptr t, Edge_ptr e) { bg.edges_to_erase(t, e); }
    void edges_erase(Vertex_ptr f, Vertex_ptr t) { bg.edges_from_to_erase(f, t); }

    string to_string() 
    {
        return "\nTYPE: Directed Graph" \
         "\nVERTICES:\n" + bg.vertices_to_string() + \
         "\nEDGES:\n" + bg.edges_to_string(edges_from());
    }
};

struct directed_acyclic_graph 
{
    base_graph bg;

    directed_acyclic_graph() {}
    directed_acyclic_graph(base_graph& base): bg(base)
    {
        _DEBUG("<directed_acyclic_graph> constructor using base_graph&");
    }

    void copy_base(base_graph& base)
    {
        bg = base;
    }

    base_graph& base() { return bg; }
    Graph_vertices& vertices() { return bg.vertices; }
    Graph_edges& edges_from() { return bg.edges_from; }
    Graph_edges& edges_to() { return bg.edges_to; }

    void vertices_insert(Vertex_ptr v) { bg.vertices_insert(v); }
    void vertices_erase(Vertex_ptr v) { bg.vertices_erase(v); }

    void edges_from_insert(Vertex_ptr f, Edge_ptr e) { bg.edges_from_insert(f, e); }
    void edges_to_insert(Vertex_ptr t, Edge_ptr e) { bg.edges_to_insert(t, e); }

    Edge_ptr edges_from_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_from_find(f, t); }
    Edge_ptr edges_to_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_to_find(f, t); }
    Edge_ptr edges_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_from_find(f, t); }

    void edges_from_erase(Vertex_ptr f, Edge_ptr e) { bg.edges_from_erase(f, e); }
    void edges_to_erase(Vertex_ptr t, Edge_ptr e) { bg.edges_to_erase(t, e); }
    void edges_erase(Vertex_ptr f, Vertex_ptr t) { bg.edges_from_to_erase(f, t); }

    /* what makes it special */
    Graph_vertices topological_order() { return Graph_vertices{}; } 

    string to_string() 
    {
        return "\nTYPE: Directed Acyclic Graph" \
         "\nVERTICES:\n" + bg.vertices_to_string() + \
         "\nEDGES:\n" + bg.edges_to_string(edges_from());
    }
};

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