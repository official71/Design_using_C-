#include <iostream>
#include "concepts.h"
#include "graph.h"
#include "graphop.h"

using namespace std;

// //template<GraphVertex GV>
// void fun(Vertex gv)
// {
//     cout << gv.to_string() << endl;
// }

void try_copy(directed_graph& dg, Vertex_ptr vp1)
{
    directed_graph copy_dg(dg.base());
    _DEBUG("COPY: ", copy_dg.to_string());

    // remove_edge(dg, ep21);
    // clear_edges_of(dg, vp1);
    remove(copy_dg, vp1);
    _DEBUG("Step 2: ", dg.to_string());

    // remove_edge(dg, vp3, vp2);
    // _DEBUG("Step 3: ", dg.to_string());

    _DEBUG("COPY Step 2: ", copy_dg.to_string());

    dg.copy_base(copy_dg.base());
    _DEBUG("Step 2.5: ", dg.to_string());
}

int main(int argc, char* argv[])
{
    // vertex bv;
    // cout << fun(bv) << endl;
    Vertex_ptr vp1(new vertex(make_pair("v1", 1)));
    // cout << vp1->to_string() << endl;

    Vertex_ptr vp2(new vertex(make_pair("v2", 2)));
    // cout << vp2->to_string() << endl;

    Vertex_ptr vp3(new vertex(make_pair("v3", 2)));

    Edge_ptr ep12(new directed_edge(vp1, vp2));
    // cout << ep->to_string() << endl;

    // cout << vp << endl;
    // cout << ep->is_to(vp) << endl;

    directed_graph dg;
    add(dg, vp1);
    add(dg, vp2);
    auto ep21 = add_edge(dg, vp2, vp1, 100);
    add_edge(dg, ep12);
    auto ep13 = add_edge(dg, vp1, vp3, 3);
    auto ep32 = add_edge(dg, vp3, vp2, 3);
    // add_edge(dg, ep2);
    _DEBUG("Step 1: ", dg.to_string());
    // _DEBUG("Adj: ", adjacent(dg, vp3, vp2));

    // for (auto v : neighbors(dg, vp3))
    //     _DEBUG("nb: ", v->to_string());

    // directed_graph copy_dg(dg.base());
    // _DEBUG("COPY: ", copy_dg.to_string());
    try_copy(dg, vp1);
    _DEBUG("Step 3: ", dg.to_string());

    // remove_edge(dg, ep21);
    // clear_edges_of(dg, vp1);
    // remove(dg, vp1);
    // _DEBUG("Step 2: ", dg.to_string());

    // remove_edge(dg, vp3, vp2);
    // _DEBUG("Step 3: ", dg.to_string());

    // _DEBUG("COPY Step 2: ", copy_dg.to_string());

    return 0;
}