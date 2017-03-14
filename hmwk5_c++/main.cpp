#include <iostream>
// #include "concepts.h"
#include "dg.h"
#include "dag.h"
#include "dt.h"
#include "graphop.h"

using namespace std;

// //template<GraphVertex GV>
// void fun(Vertex gv)
// {
//     cout << gv.to_string() << endl;
// }

void construct_graph_1(directed_graph& dg)
{
    Vertex_ptr b(new vertex(make_pair("b", 2)));
    Vertex_ptr c(new vertex(make_pair("c", 3)));
    Vertex_ptr d(new vertex(make_pair("d", 4)));
    Vertex_ptr e(new vertex(make_pair("e", 5)));
    Vertex_ptr a(new vertex(make_pair("a", 1)));
    Vertex_ptr f(new vertex(make_pair("f", 6)));
    Vertex_ptr g(new vertex(make_pair("g", 7)));
    Vertex_ptr h(new vertex(make_pair("h", 8)));
    Vertex_ptr i(new vertex(make_pair("i", 9)));

    add(dg, a);
    add(dg, b);
    add(dg, c);
    add(dg, d);
    add(dg, e);
    add(dg, f);
    add(dg, g);
    add(dg, h);
    add(dg, i);

    auto ab = add_edge(dg, a, b, 100);
    auto bc = add_edge(dg, b, c, 200);
    auto cd = add_edge(dg, c, d, 300);
    auto ce = add_edge(dg, c, e, 400);
    auto bf = add_edge(dg, b, f, 500);
    auto fg = add_edge(dg, f, g, 600);
    auto gh = add_edge(dg, g, h, 700);
    auto fi = add_edge(dg, f, i, 800);
    /* this looks like a cycle but is not */
    auto ig = add_edge(dg, i, g, 900);
    /* cyclic now */
    auto eb = add_edge(dg, e, b, 1000);
}

vector<Vertex_ptr> init_vector_of_vertices_1()
{
    vector<Vertex_ptr> vv {};
    
    int i = 1;
    char c = 'a';
    for (; i < 10; ++i, ++c)
        vv.push_back(make_shared<vertex>(vertex(make_pair(string(1, c), i))));
    return vv;
}

vector<Edge_ptr> init_vector_of_edges_1(vector<Vertex_ptr>& vv)
{
    vector<Edge_ptr> ve {};

    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[1], 100)));
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[1], vv[2], 200)));
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[2], vv[3], 300)));
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[2], vv[4], 400)));
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[1], vv[5], 500)));
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[5], vv[6], 600)));
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[6], vv[7], 700)));
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[5], vv[8], 800)));
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[8], vv[6], 900)));
    // ve.push_back(make_shared<directed_edge>(directed_edge(vv[4], vv[1], 1000)));

    return ve;
}

vector<Edge_ptr> init_vector_of_edges_2(vector<Vertex_ptr>& vv)
{
    vector<Edge_ptr> ve {};
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[1], 100))); //a->b
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[2], 200))); //a->c
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[2], vv[3], 300))); //c->d
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[3], vv[4], 400))); //d->e
    return ve;
}

vector<Edge_ptr> init_vector_of_edges_3(vector<Vertex_ptr>& vv)
{
    vector<Edge_ptr> ve {};
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[3], vv[1], 100))); //d->b
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[3], vv[2], 200))); //d->c
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[2], vv[0], 300))); //c->a
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[4], 400))); //a->e
    return ve;
}

vector<Edge_ptr> init_vector_of_edges_4(vector<Vertex_ptr>& vv)
{
    vector<Edge_ptr> ve {};
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[1], 100))); //a->b
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[2], 200))); //a->c
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[2], vv[3], 300))); //c->d
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[3], vv[4], 400))); //d->e
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[1], vv[3], 500))); //b->d
    return ve;
}

vector<Edge_ptr> init_vector_of_edges_5(vector<Vertex_ptr>& vv)
{
    vector<Edge_ptr> ve {};
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[1], 100))); //a->b
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[2], 200))); //a->c
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[3], vv[4], 400))); //d->e
    return ve;
}

vector<Edge_ptr> init_vector_of_edges_6(vector<Vertex_ptr>& vv)
{
    vector<Edge_ptr> ve {};
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[1], 100))); //a->b
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[0], vv[2], 200))); //a->c
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[2], vv[3], 300))); //c->d
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[3], vv[4], 400))); //d->e
    ve.push_back(make_shared<directed_edge>(directed_edge(vv[4], vv[0], 500))); //e->a
    return ve;
}

void try_dt()
{
    auto vv = init_vector_of_vertices_1();

    auto ve1 = init_vector_of_edges_2(vv);
    directed_tree dt1(ve1, vv[0]);
    _DEBUG("------------dt #1: ", dt1.to_string());

    add(dt1, vv[5]);
    _DEBUG("------------dt STEP 1: ", dt1.to_string());

    /* add edge c->f */
    add_edge(dt1, make_shared<directed_edge>(directed_edge(vv[2], vv[5], 1000)));
    _DEBUG("------------dt STEP 2: ", dt1.to_string());

    /* add edge e->f */
    add_edge(dt1, make_shared<directed_edge>(directed_edge(vv[4], vv[5], 2000)));
    _DEBUG("------------dt STEP 3: ", dt1.to_string());

    /* add edge g->h */
    add_edge(dt1, make_shared<directed_edge>(directed_edge(vv[6], vv[7], 1000)));
    _DEBUG("------------dt STEP 4: ", dt1.to_string());

    /* remove node d */
    remove(dt1, vv[3]);
    _DEBUG("------------dt STEP 5: ", dt1.to_string());

    /* remove node e */
    remove(dt1, vv[4]);
    _DEBUG("------------dt STEP 6: ", dt1.to_string());

    // auto ve2 = init_vector_of_edges_3(vv);
    // directed_tree dt2(ve2, vv[3]);
    // _DEBUG("------------dt #2: ", dt2.to_string());

    // auto ve3 = init_vector_of_edges_4(vv);
    // directed_tree dt3(ve3, vv[0]);
    // _DEBUG("------------dt #3: ", dt3.to_string());

    // auto ve4 = init_vector_of_edges_5(vv);
    // directed_tree dt4(ve4, vv[0]);
    // _DEBUG("------------dt #4: ", dt4.to_string());

    // auto ve5 = init_vector_of_edges_6(vv);
    // directed_tree dt5(ve5, vv[0]);
    // _DEBUG("------------dt #5: ", dt5.to_string());
}

void try_new_graph()
{
    auto vv = init_vector_of_vertices_1();
    auto ve = init_vector_of_edges_1(vv);

    directed_graph dg(vv, ve);
    // add_edge(dg, ve[0]);
    _DEBUG("dg: ", dg.to_string());
    _DEBUG("dg is cyclic: ", dg.is_cyclic());

    directed_acyclic_graph dag(vv, ve);
    // add_edge(dag, ve[0]);
    _DEBUG("dag: ", dag.to_string());
    _DEBUG("dag is cyclic: ", dag.is_cyclic());

    /* try adding a cyclic edge */
    add_edge(dg, make_shared<directed_edge>(directed_edge(vv[4], vv[1], 1000)));
    _DEBUG("dg STEP 2: ", dg.to_string());
    _DEBUG("dg is cyclic: ", dg.is_cyclic());

    add_edge(dag, make_shared<directed_edge>(directed_edge(vv[4], vv[1], 1000)));
    _DEBUG("dag STEP 2: ", dag.to_string());
    _DEBUG("dag is cyclic: ", dag.is_cyclic());

    /* try removing a key vertex */
    remove(dg, vv[1]);
    _DEBUG("dg STEP 3: ", dg.to_string());
    _DEBUG("dg is cyclic: ", dg.is_cyclic());

    remove(dag, vv[1]);
    _DEBUG("dag STEP 3: ", dag.to_string());
    _DEBUG("dag is cyclic: ", dag.is_cyclic());
}

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

void try_dfs()
{
    directed_graph dg;
    construct_graph_1(dg);

    _DEBUG("Graph bg: ", dg.to_string());

    depth_first_search DFS1;
    _DEBUG("DFS1 created... try cyclic: ", DFS1.is_cyclic(dg.base()));

    depth_first_search DFS;
    _DEBUG("DFS created... try cyclic: ", DFS.is_cyclic());

    // auto start = dg.base().vertices_find_by_value(make_pair("a",1));
    // DFS.dfs(false, start);
    DFS.dfs(dg.base(), dg.base().vertices_find_by_value(make_pair("b",2)));
    _DEBUG("Retry cyclic: ", DFS.is_cyclic());

    // int num_cycles();
    // map<int, vector<Vertex_ptr>> get_cycles();
    // map<Vertex_ptr, pair<int, int>> get_orders();
    // map<Vertex_ptr, Vertex_ptr> get_parents();

    auto nr_cycles = DFS.num_cycles();
    _DEBUG("nr_cycles = ", std::to_string(nr_cycles));

    auto cycles = DFS.get_cycles();
    for (auto cp : cycles) {
        _DEBUG("Cycle: ", std::to_string(cp.first));
        for (auto v : cp.second) {
            _DEBUG("    ", v->to_string());
        }
    }

    auto orders = DFS.get_orders();
    for (auto op : orders) {
        _DEBUG("order of ", op.first->to_string(), ": ", \
            std::to_string(op.second.first), ",\t", \
            std::to_string(op.second.second));
    }

    _DEBUG("Vertices in order: ");
    auto vertices_order = DFS.vertices_in_order(dg.base().vertices_find_by_value(make_pair("a",1)));
    for (auto vo : vertices_order) {
        _DEBUG(vo->to_string());
    }

    auto parents = DFS.get_parents();
    for (auto pp : parents) {
        string str = pp.second ? pp.second->to_string() : "NULL";
        _DEBUG("parent of ", pp.first->to_string(), ": ", str);
    }

    auto top = DFS.get_top_vertex();
    _DEBUG("top vertex: ", top ? top->to_string() : "NULL");

    _DEBUG("reachable from top vertex: ", DFS.reachable_from_vertex(dg.base(), top));
    _DEBUG("reachable from arbitrary vertex: ", \
        DFS.reachable_from_vertex(dg.base(), dg.base().vertices_find_by_value(make_pair("b",2))));
}

int main(int argc, char* argv[])
{
    try_dfs();
    // try_new_graph();
    // try_dt();
#if 0
    // vertex bv;
    // cout << fun(bv) << endl;
    Vertex_ptr vp1(new vertex(make_pair("v1", 1)));
    // cout << vp1->to_string() << endl;

    Vertex_ptr vp2(new vertex(make_pair("v2", 2)));
    // cout << vp2->to_string() << endl;

    Vertex_ptr vp3(new vertex(make_pair("v3", 2)));
    Vertex_ptr vp4(new vertex(make_pair("v4", 5100)));

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
    // try_copy(dg, vp1);
    // _DEBUG("Step 3: ", dg.to_string());

    directed_acyclic_graph dag(dg.base());
    add(dag, vp4);
    _DEBUG("DAG: ", dag.to_string());
#endif
    return 0;
}