#ifndef _GMAKER_H
#define _GMAKER_H

#include <map>
#include <vector>
#include <string>
#include "basic.h"

using namespace std;

map<string, Vertex_ptr> all_vertices;
map<string, Edge_ptr> all_edges;
typedef pair<vector<Vertex_ptr>, vector<Edge_ptr>> PVE;

void generate_all_vertices()
{
    int i = 0;
    char c = 'a';
    for (; c <= 'z'; ++i, ++c)
        all_vertices[string(1, c)] = make_shared<vertex>(vertex(make_pair(string(1, c), i)));
}

void generate_all_edges()
{
    int i = 100;
    for (auto x : all_vertices) {
        for (auto y : all_vertices) {
            if (x.first == y.first)
                continue;
            all_edges[x.first + y.first] = make_shared<directed_edge>(
                directed_edge(x.second, y.second, i++));
        }
    }
}

PVE ve_dag()
{
    vector<Vertex_ptr> vv;
    vector<Edge_ptr> ve;

    vv.push_back(all_vertices["a"]);
    vv.push_back(all_vertices["b"]);
    vv.push_back(all_vertices["c"]);
    vv.push_back(all_vertices["d"]);
    vv.push_back(all_vertices["e"]);
    vv.push_back(all_vertices["f"]);
    vv.push_back(all_vertices["g"]);
    vv.push_back(all_vertices["h"]);
    vv.push_back(all_vertices["i"]);

    ve.push_back(all_edges["ab"]);
    ve.push_back(all_edges["bc"]);
    ve.push_back(all_edges["bf"]);
    ve.push_back(all_edges["cd"]);
    ve.push_back(all_edges["fg"]);
    ve.push_back(all_edges["ce"]);
    ve.push_back(all_edges["gh"]);
    ve.push_back(all_edges["fi"]);

    return make_pair(vv, ve);
}

PVE ve_dg_cyclic()
{
    vector<Vertex_ptr> vv;
    vector<Edge_ptr> ve;

    vv.push_back(all_vertices["a"]);
    vv.push_back(all_vertices["b"]);
    vv.push_back(all_vertices["c"]);
    vv.push_back(all_vertices["d"]);
    vv.push_back(all_vertices["e"]);
    vv.push_back(all_vertices["f"]);
    vv.push_back(all_vertices["g"]);
    vv.push_back(all_vertices["h"]);
    vv.push_back(all_vertices["i"]);

    ve.push_back(all_edges["ab"]);
    ve.push_back(all_edges["bc"]);
    ve.push_back(all_edges["bf"]);
    ve.push_back(all_edges["cd"]);
    ve.push_back(all_edges["fg"]);
    ve.push_back(all_edges["ce"]);
    ve.push_back(all_edges["gh"]);
    ve.push_back(all_edges["fi"]);
    //add one cycle
    ve.push_back(all_edges["eb"]);
    //yet another cycle
    ve.push_back(all_edges["ia"]);


    return make_pair(vv, ve);
}

PVE ve_dt()
{
    vector<Vertex_ptr> vv;
    vector<Edge_ptr> ve;

    vv.push_back(all_vertices["a"]);

    ve.push_back(all_edges["ab"]);
    ve.push_back(all_edges["bc"]);
    ve.push_back(all_edges["bf"]);
    ve.push_back(all_edges["cd"]);
    ve.push_back(all_edges["fg"]);
    ve.push_back(all_edges["ce"]);
    ve.push_back(all_edges["gh"]);
    ve.push_back(all_edges["fi"]);

    return make_pair(vv, ve);
}

#endif