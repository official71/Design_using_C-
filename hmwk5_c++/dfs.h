#ifndef _DFS_H
#define _DFS_H

#include <vector>
#include <set>
#include <map>
#include "basic.h"

using namespace std;

enum Color { White, Gray, Black };

class depth_first_search
{

private:
    base_graph bg; /* input graph directed */

    /* outputs */
    map<Vertex_ptr, pair<int, int>> orders {}; /* <discovery, finish> time orders */
    map<Vertex_ptr, Vertex_ptr> parents {}; /* <child, parent> relations */

    bool cyclic = false;
    int nr_cycles = 0;
    map<int, vector<Vertex_ptr>> cycles {};

    /* runtime data */
    int time = -1; /* set to 0 before kickoff */
    bool is_valid() { return time >= 0; }
    bool cyclic_break_flag = false; /* whether breaks the dfs if found cyclic */

    map<Vertex_ptr, Color> colors {}; /* White=undiscovered, Gray=active, Black=finished */
    map<Vertex_ptr, bool> marked {}; /* marked ? true:false */

    /* iterating function */
    void dfs_iter(Vertex_ptr vp);

    /* reconstruct cycle function */
    void record_cycle(Vertex_ptr u, Vertex_ptr v);

public:
    depth_first_search(base_graph& base);
    ~depth_first_search() {}

    bool is_cyclic();
    int num_cycles();
    map<int, vector<Vertex_ptr>> get_cycles();

    map<Vertex_ptr, pair<int, int>> get_orders();
    map<Vertex_ptr, Vertex_ptr> get_parents();

    bool dfs(bool break_if_cyclic=false);
};

depth_first_search::depth_first_search(base_graph& base) : bg(base) {}

bool depth_first_search::is_cyclic()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running dfs...");
    return cyclic;
}

int depth_first_search::num_cycles()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running dfs...");
    return nr_cycles;
}

map<int, vector<Vertex_ptr>> depth_first_search::get_cycles()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running dfs...");
    return cycles;
}

map<Vertex_ptr, pair<int, int>> depth_first_search::get_orders()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running dfs...");
    return orders;
}

map<Vertex_ptr, Vertex_ptr> depth_first_search::get_parents()
{
    if (!is_valid())
        _DEBUG("Attempt to query dfs data without running dfs...");
    return parents;
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

void depth_first_search::dfs_iter(Vertex_ptr u)
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
            dfs_iter(v);
            if (cyclic && cyclic_break_flag)
                return;
        }
    }

    colors[u] = Black; /* finished */
    orders[u].second = ++time; /* set finish time */
}

bool depth_first_search::dfs(bool break_if_cyclic)
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

    for(auto vp : bg.vertices) {
        if (!marked[vp]) {
            /* dive into iterations */
            dfs_iter(vp);
            if (cyclic && cyclic_break_flag)
                break;
        }
    }

    return cyclic;
}

#endif