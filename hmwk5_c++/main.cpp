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

int main(int argc, char* argv[])
{
    // vertex bv;
    // cout << fun(bv) << endl;
    Vertex_ptr vp1(new vertex(make_pair("v1", 1)));
    // cout << vp1->to_string() << endl;

    Vertex_ptr vp2(new vertex(make_pair("v2", 2)));
    // cout << vp2->to_string() << endl;

    Edge_ptr ep(new directed_edge(vp1, vp2));
    // cout << ep->to_string() << endl;

    // cout << vp << endl;
    // cout << ep->is_to(vp) << endl;

    directed_graph dg;
    add(dg, vp1);
    add(dg, vp2);
    // auto nep = add_edge(dg, vp1, vp2, 100);
    add_edge(dg, ep);
    // add_edge(dg, nep);
    _DEBUG("debug ", dg.to_string());

    return 0;
}