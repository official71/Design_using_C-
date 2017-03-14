#ifndef _DFS_H
#define _DFS_H

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "basic.h"

using namespace std;

enum Color { White, Gray, Black };

class depth_first_search
{

private:
    // base_graph bg; /* input graph directed */

    /* outputs */
    map<Vertex_ptr, pair<int, int>> orders {}; /* <discovery, finish> time orders */
    map<Vertex_ptr, Vertex_ptr> parents {}; /* <child, parent> relations */
    Vertex_ptr top_vertex = NULL; /* last-finishing vertex in DFS */

    bool cyclic = false;
    int nr_cycles = 0;
    map<int, vector<Vertex_ptr>> cycles {};

    /* runtime data */
    int time = -1; /* set to 0 before kickoff */
    int max_finishing_time = -1;
    bool cyclic_break_flag = false; /* whether breaks the dfs if found cyclic */
    bool is_valid() { return time >= 0 && !cyclic_break_flag; }

    map<Vertex_ptr, Color> colors {}; /* White=undiscovered, Gray=active, Black=finished */
    map<Vertex_ptr, bool> marked {}; /* marked ? true:false */

    void save_top_vertex();

    /* dfs function */
    void dfs_iter(base_graph& bg, Vertex_ptr vp);
    bool run_dfs(base_graph& bg, bool break_if_cyclic, Vertex_ptr start);

    /* reconstruct cycle function */
    void record_cycle(Vertex_ptr u, Vertex_ptr v);


public:
    // depth_first_search(base_graph& base);
    depth_first_search() {}
    ~depth_first_search() {}

    vector<Vertex_ptr> dfs(base_graph& bg, Vertex_ptr start=NULL);
    bool reachable_from_vertex(base_graph& bg, Vertex_ptr start);
    bool is_cyclic(base_graph& bg);
    
    /* following methods must be called after running dfs on the graph */
    bool is_cyclic();
    int num_cycles();
    map<int, vector<Vertex_ptr>> get_cycles();

    vector<Vertex_ptr> vertices_in_order();
    map<Vertex_ptr, pair<int, int>> get_orders();
    map<Vertex_ptr, Vertex_ptr> get_parents();
    Vertex_ptr get_top_vertex();
};

// depth_first_search::depth_first_search(base_graph& base) : bg(base) {}

bool depth_first_search::is_cyclic()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running full dfs...");
    return cyclic;
}

int depth_first_search::num_cycles()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running full dfs...");
    return nr_cycles;
}

map<int, vector<Vertex_ptr>> depth_first_search::get_cycles()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running full dfs...");
    return cycles;
}

vector<Vertex_ptr> depth_first_search::vertices_in_order()
{
    vector<Vertex_ptr> vec;
    if (!is_valid()) {
        _DEBUG("Attempt to query dfs data without running full dfs...");
        return vec;
    }

    vector<pair<Vertex_ptr, int>> tmp;
    for (auto p : orders)
        tmp.push_back(make_pair(p.first, p.second.first));
    sort(tmp.begin(), tmp.end(), 
        [](const pair<Vertex_ptr, int>& u, const pair<Vertex_ptr, int>& v) \
        {return u.second < v.second;});

    for (auto t : tmp)
        vec.push_back(t.first);
    return vec;
}

map<Vertex_ptr, pair<int, int>> depth_first_search::get_orders()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running full dfs...");
    return orders;
}

map<Vertex_ptr, Vertex_ptr> depth_first_search::get_parents()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running full dfs...");
    return parents;
}

Vertex_ptr depth_first_search::get_top_vertex()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running full dfs...");
    return top_vertex;
}

/* u is the current vertex, there is edge u -> v, and v is Gray(active)
 * ==> cycle
 */
void depth_first_search::record_cycle(Vertex_ptr u, Vertex_ptr v)
{
    // auto vv = cycles[++nr_cycles];
    vector<Vertex_ptr> vv {};
    vv.push_back(u);

    auto parent = parents[u];
    while (parent) {
        vv.push_back(parent);
        if (parent == v)
            break;
        parent = parents[parent];
    }

    cycles[++nr_cycles] = vv;
}

void depth_first_search::dfs_iter(base_graph& bg, Vertex_ptr u)
{
    marked[u] = true;
    colors[u] = Gray; /* discovered, in stack */
    orders[u].first = ++time; /* set discovery time */

    for (auto v : bg.edges_from_neighbors(u)) {
        if (marked[v]) {
            if (colors[v] == Gray) {
                /* Cycle detected */
                cyclic = true;
                record_cycle(u, v);
                if (cyclic_break_flag)
                    return;
            }
        } else {
            /* v is not marked/discovered */
            parents[v] = u;
            dfs_iter(bg, v);
            if (cyclic && cyclic_break_flag)
                return;
        }
    }

    colors[u] = Black; /* finished */
    orders[u].second = ++time; /* set finish time */
}

bool depth_first_search::run_dfs(base_graph& bg, bool break_if_cyclic, Vertex_ptr start)
{
    time = 0; /* everything is valid now */
    cyclic_break_flag = break_if_cyclic;

    /* initialize */
    for (auto vp : bg.vertices) {
        marked[vp] = false;
        parents[vp] = NULL;
        colors[vp] = White;
        orders[vp] = make_pair(0, 0);
    }

    if (start && bg.vertices.find(start) != bg.vertices.end()) {
        /* if the starting vertex is specified */
        dfs_iter(bg, start);
        if (cyclic && cyclic_break_flag)
            return cyclic;
    }

    for(auto vp : bg.vertices) {
        if (!marked[vp]) {
            /* dive into iterations */
            dfs_iter(bg, vp);
            if (cyclic && cyclic_break_flag)
                break;
        }
    }

    /* save the last finishing vertex and its finishing time */
    max_finishing_time = time;
    save_top_vertex();

    return cyclic;
}

vector<Vertex_ptr> depth_first_search::dfs(base_graph& bg, Vertex_ptr start)
{
    run_dfs(bg, false, start);
    return vertices_in_order();
}

bool depth_first_search::is_cyclic(base_graph& bg)
{
    return run_dfs(bg, true, NULL);
}

/* 
 * The "top" vertex is defined as the last-finishing vertex in DFS
 * If the graph is connected and acyclic, it is the first in topological order 
 */
void depth_first_search::save_top_vertex()
{
    for (auto p : orders) {
        if (p.second.second == max_finishing_time)
            top_vertex = p.first;
    }
}

bool depth_first_search::reachable_from_vertex(base_graph& bg, Vertex_ptr start)
{
    if (!start) {
        _DEBUG("NULL input vertex.");
        return false;
    }
    if (bg.vertices.find(start) == bg.vertices.end()) {
        _DEBUG("Input vertex is not in the graph.");
        return false;
    }

    /* run dfs from the given vertex */
    _DEBUG("Run DFS from input vertex...");
    dfs(bg, start);

    /* check the finishing time of the given vertex */
    return max_finishing_time == orders[start].second;
}

#endif