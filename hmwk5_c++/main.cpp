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
    vertex_ptr vp(new vertex(make_pair("v1", 1)));
    cout << vp->to_string() << endl;

    vertex_ptr vp1(new vertex(make_pair("v2", 2)));
    cout << vp1->to_string() << endl;

    edge_ptr ep(new directed_edge(vp, vp1));
    cout << ep->to_string() << endl;

    cout << vp << endl;
    cout << ep->is_to(vp) << endl;

    return 0;
}