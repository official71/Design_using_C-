#ifndef _DT_H
#define _DT_H

#include <string>
#include <utility>
#include <memory>
#include <set>
#include <map>
#include <vector>
// #include "concepts.h"
#include "basic.h"
#include "dfs.h"

using namespace std;

struct directed_tree
{
    base_graph bg;
    Vertex_ptr root_node = NULL;

    directed_tree(Vertex_ptr root);
    directed_tree(base_graph& base, Vertex_ptr root);
    directed_tree(vector<Edge_ptr>& ve, Vertex_ptr root);

    void copy_base(base_graph& base, Vertex_ptr root, bool trusted=false);

    base_graph& base() { return bg; }
    Graph_vertices& vertices() { return bg.vertices; }
    Graph_edges& edges_from() { return bg.edges_from; }
    Graph_edges& edges_to() { return bg.edges_to; }

    bool has_vertex(Vertex_ptr v) { return bg.vertex_in_graph(v); }
    bool has_edge(Edge_ptr e) { return bg.edge_in_graph(e); }

    Val value(Vertex_ptr v) { return bg.vertex_value(v); }
    Val value(Edge_ptr e) { return bg.edge_value(e); }
    void set_value(Vertex_ptr v, Val val) { bg.set_vertex_value(v, val); }
    void set_value(Edge_ptr e, Val val) { bg.set_edge_value(e, val); }

    void vertices_insert(Vertex_ptr v) { bg.vertices_insert(v); }
    void vertices_erase(Vertex_ptr v) { bg.vertices_erase(v); }

    void edges_from_insert(Vertex_ptr f, Edge_ptr e) { bg.edges_from_insert(f, e); }
    void edges_to_insert(Vertex_ptr t, Edge_ptr e) { bg.edges_to_insert(t, e); }

    Edge_ptr edges_from_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_from_find(f, t); }
    Edge_ptr edges_to_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_to_find(f, t); }
    Edge_ptr edges_find(Vertex_ptr f, Vertex_ptr t) { return bg.edges_from_find(f, t); }

    Graph_vertices edges_from_neighbors(Vertex_ptr f) { return bg.edges_from_neighbors(f); }
    Graph_vertices children(Vertex_ptr f) { return bg.edges_from_neighbors(f); }
    Graph_vertices edges_to_neighbors(Vertex_ptr t) { return bg.edges_to_neighbors(t); }
    Graph_vertices parent(Vertex_ptr t) { return bg.edges_to_neighbors(t); }
    bool is_leaf(Vertex_ptr x) { return children(x).size() == 0; }

    void edges_from_erase(Vertex_ptr f, Edge_ptr e) { bg.edges_from_erase(f, e); }
    void edges_to_erase(Vertex_ptr t, Edge_ptr e) { bg.edges_to_erase(t, e); }
    void edges_erase(Vertex_ptr f, Vertex_ptr t) { bg.edges_from_to_erase(f, t); }

    /* what makes it special */
    Vertex_ptr root() { return root_node; }
    void set_root(Vertex_ptr vp) { root_node = vp; }
    bool has_root() { return root_node != NULL; }

    vector<Vertex_ptr> topological_order();

    string to_string() 
    {
        return !root_node ? "\nINVALID DIRECTED TREE (ROOT IS NULL)" : \
         "\nTYPE: Directed Tree" \
         "\nRoot:" + root_node->to_string() +\
         "\nVERTICES:\n" + bg.vertices_to_string() + \
         "\nEDGES:\n" + bg.edges_to_string(edges_from());
    }
};

bool is_directed_tree(base_graph& bg, Vertex_ptr root)
{
    /* validate root node */
    if (!root) {
        _DEBUG("Null root node.");
        return false;
    }
    if (bg.vertices.find(root) == bg.vertices.end()) {
        _DEBUG("Root node is not in the graph.");
        return false;
    }

    /* Root has no parent.
     * Each node (except root) must have exactly one parent node.
     * Provided this, if the graph is not cyclic, then every node must be reachable 
     * from root.
     */
    for (auto v : bg.vertices) {
        auto search = bg.edges_to.find(v);
        if (v == root) {
            if (search != bg.edges_to.end() && search->second.size() != 0) {
                _DEBUG("Root node has parent.");
                return false;
            }
        }
        else {
            if (search == bg.edges_to.end()) {
                _DEBUG("Node: ", v->to_string(), " has no parent.");
                return false;
            }
            if (search->second.size() != 1) {
                _DEBUG("Node: ", v->to_string(), \
                    " has unexpected number of parents: ", \
                    search->second.size());
                return false;
            }
        }
    }

    /* graph must be acyclic */
    depth_first_search DFS;
    return !DFS.is_cyclic(bg);
}

directed_tree::directed_tree(Vertex_ptr root)
{
    if (root) {
        vertices_insert(root);
        set_root(root);
    }
    else
        _DEBUG("NULL root node");
}

directed_tree::directed_tree(base_graph& base, Vertex_ptr root)
{
    if (is_directed_tree(base, root)) {
        copy_base(base, root, true);
        set_root(root);
    }
    else
        _DEBUG("ERROR: DT not constructed, input violates DT criteria.");
}

directed_tree::directed_tree(vector<Edge_ptr>& ve, Vertex_ptr root)
{
    base_graph tmp_bg = base_graph(ve);
    if (is_directed_tree(tmp_bg, root)) {
        copy_base(tmp_bg, root, true);
        set_root(root);
    }
    else
        _DEBUG("ERROR: DT not constructed, input violates DT criteria.");
}

void directed_tree::copy_base(base_graph& base, Vertex_ptr root, bool trusted)
{
    bool dt = true;
    if (!trusted)
        dt = is_directed_tree(base, root);

    if (dt)
        bg = base;
    else
        _DEBUG("ERROR: DT not updated, input violates DT criteria.");
}


vector<Vertex_ptr> directed_tree::topological_order()
{
    depth_first_search DFS;
    return DFS.dfs(bg);
}
#endif