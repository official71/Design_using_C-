#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "dg.h"
#include "dag.h"
#include "dt.h"
#include "graphop.h"
#include "gmaker.h"

using namespace std;


Retval test_directed_graph()
{
    cout << "\n\n---------------------------------------------" << endl;
    cout << "    TEST DIRECTED GRAPH" << endl;
    cout << "---------------------------------------------" << endl;

    PVE pve = ve_dg_cyclic();
    directed_graph testgraph_dg_cyclic(pve.first, pve.second);
    depth_first_search DFS;

    /* print graph */
    cout << "\n    1. PRINT GRAPH: " << endl;
    print(testgraph_dg_cyclic);

    /* count vertices and edges */
    cout << "\n    2. COUNT: " << endl;
    cout << "Number of vertices = " << count_vertices(testgraph_dg_cyclic) << endl;
    cout << "Number of edges    = " << count_edges(testgraph_dg_cyclic) << endl;

    /* check reachability from top */
    cout << "\n    3. REACHABLE FROM TOP: " << endl;
    auto vtop = top(testgraph_dg_cyclic);
    if (vtop) {
        cout << "Top vertex: " << vtop->to_string() << endl;
        if (DFS.reachable_from_vertex(testgraph_dg_cyclic.base(), vtop))
            cout << "Every vertex is reachable from top; graph is connected." << endl;
        else
            cout << "Graph is not connected." << endl;
    } else {
        cout << "Top vertex is NULL." << endl;
        return Failure;
    }

    /* find cycles */
    cout << "\n    4. FIND CYCLES: " << endl;
    DFS.dfs(testgraph_dg_cyclic.base(), vtop);
    if (DFS.is_cyclic()) {
        cout << std::to_string(DFS.num_cycles()) << " cycle(s) found:" << endl;
        for (auto cp : DFS.get_cycles()) {
            cout << "Cycle #" << std::to_string(cp.first) << ": ";
            for (auto v : cp.second)
                cout << v->to_string() << "  ";
            cout << endl;
        }
    } else
        cout << "No cycles found; graph is acyclic";

    /* list vertices and edges in descending order of values */
    cout << "\n    5. ORDER BY VALUE: " << endl;
    cout << "List of vertices: " << endl;
    auto vertices_ordered = order_vertices_by_value(testgraph_dg_cyclic, true);
    int c = 0;
    for (auto vo : vertices_ordered) {
        cout << vo->to_string() << "  ";
        if (++c % 9 == 0)
            cout << endl;
    }
    cout << "List of edges: " << endl;
    auto edges_ordered = order_edges_by_value(testgraph_dg_cyclic, true);
    c = 0;
    for (auto eo : edges_ordered) {
        cout << eo->to_string() << "  ";
        if (++c % 3 == 0)
            cout << endl;
    }
    cout << endl;

    /* add edge */
    cout << "\n    6. ADD EDGE: " << endl;
    cout << "Trying to add edge that causes cycle: " << all_edges["ib"]->to_string() << " ..." << endl;
    if (add_edge(testgraph_dg_cyclic, all_edges["ib"]) == Success) {
        cout << "Operation SUCCESS. New graph:" << endl;
        print(testgraph_dg_cyclic);
    } else {
        cout << "Operation FAILED." << endl;
        return Failure;
    }

    /* remove edge */
    cout << "\n    7. REMOVE EDGE: " << endl;
    cout << "Trying to remove edge that breaks connectivity: " << all_edges["fg"]->to_string() << " ..." << endl;
    if (remove_edge(testgraph_dg_cyclic, all_edges["fg"])) {
        cout << "Operation SUCCESS. New graph:" << endl;
        print(testgraph_dg_cyclic);

        vtop = top(testgraph_dg_cyclic);
        if (vtop) {
            cout << "New top vertex: " << vtop->to_string() << endl;
            if (DFS.reachable_from_vertex(testgraph_dg_cyclic.base(), vtop)) {
                cout << "ERROR: Every vertex is reachable from top; graph is connected." << endl;
                return Failure;
            }
            else
                cout << "Graph is not connected." << endl;
        } else {
            cout << "Top vertex is NULL." << endl;
            return Failure;
        }
    } else {
        cout << "Operation FAILED." << endl;
        return Failure;
    }

    return Success;
}

Retval test_directed_acyclic_graph()
{
    cout << "\n\n---------------------------------------------" << endl;
    cout << "    TEST DIRECTED ACYCLIC GRAPH" << endl;
    cout << "---------------------------------------------" << endl;

    PVE pve = ve_dag();
    directed_acyclic_graph testgraph_dag(pve.first, pve.second);
    depth_first_search DFS;

    /* print graph */
    cout << "\n    1. PRINT GRAPH: " << endl;
    print(testgraph_dag);

    /* count vertices and edges */
    cout << "\n    2. COUNT: " << endl;
    cout << "Number of vertices = " << count_vertices(testgraph_dag) << endl;
    cout << "Number of edges    = " << count_edges(testgraph_dag) << endl;

    /* check reachability from top */
    cout << "\n    3. REACHABLE FROM TOP: " << endl;
    auto vtop = top(testgraph_dag);
    if (vtop) {
        cout << "Top vertex: " << vtop->to_string() << endl;
        if (DFS.reachable_from_vertex(testgraph_dag.base(), vtop))
            cout << "Every vertex is reachable from top; graph is connected." << endl;
        else
            cout << "Graph is not connected." << endl;
    } else {
        cout << "Top vertex is NULL." << endl;
        return Failure;
    }

    /* find cycles */
    cout << "\n    4. FIND CYCLES: " << endl;
    DFS.dfs(testgraph_dag.base(), vtop);
    if (DFS.is_cyclic()) {
        cout << "Error: " << std::to_string(DFS.num_cycles()) << " cycle(s) found:" << endl;
        for (auto cp : DFS.get_cycles()) {
            cout << "Cycle #" << std::to_string(cp.first) << ": ";
            for (auto v : cp.second)
                cout << v->to_string() << "  ";
            cout << endl;
        }
        return Failure;
    } else
        cout << "No cycles found; graph is acyclic as expected";

    /* list vertices and edges in descending order of values */
    cout << "\n    5. ORDER BY VALUE: " << endl;
    cout << "List of vertices: " << endl;
    auto vertices_ordered = order_vertices_by_value(testgraph_dag, true);
    int c = 0;
    for (auto vo : vertices_ordered) {
        cout << vo->to_string() << "  ";
        if (++c % 9 == 0)
            cout << endl;
    }
    cout << "List of edges: " << endl;
    auto edges_ordered = order_edges_by_value(testgraph_dag, true);
    c = 0;
    for (auto eo : edges_ordered) {
        cout << eo->to_string() << "  ";
        if (++c % 3 == 0)
            cout << endl;
    }
    cout << endl;

    /* add edge */
    cout << "\n    6. ADD EDGE: " << endl;
    cout << "Trying to add edge that causes cycle: " << all_edges["ib"]->to_string() << " ..." << endl;
    if (add_edge(testgraph_dag, all_edges["ib"]) == Success) {
        cout << "ERROR: added invalid edge. New graph:" << endl;
        print(testgraph_dag);
        return Failure;
    } else {
        cout << "Operation FAILED, as expected." << endl;
    }

    /* remove edge */
    cout << "\n    7. REMOVE EDGE: " << endl;
    cout << "Trying to remove edge that breaks connectivity: " << all_edges["fg"]->to_string() << " ..." << endl;
    if (remove_edge(testgraph_dag, all_edges["fg"])) {
        cout << "Operation SUCCESS. New graph:" << endl;
        print(testgraph_dag);

        vtop = top(testgraph_dag);
        if (vtop) {
            cout << "New top vertex: " << vtop->to_string() << endl;
            if (DFS.reachable_from_vertex(testgraph_dag.base(), vtop)) {
                cout << "ERROR: Every vertex is reachable from top; graph is connected." << endl;
                return Failure;
            }
            else
                cout << "Graph is not connected." << endl;
        } else {
            cout << "Top vertex is NULL." << endl;
            return Failure;
        }
    } else {
        cout << "Operation FAILED." << endl;
        return Failure;
    }

    return Success;
}

Retval test_directed_tree()
{
    cout << "\n\n---------------------------------------------" << endl;
    cout << "    TEST DIRECTED TREE" << endl;
    cout << "---------------------------------------------" << endl;

    PVE pve = ve_dt();
    directed_tree testgraph_dt(pve.second, pve.first[0]);
    depth_first_search DFS;

    /* print graph */
    cout << "\n    1. PRINT TREE: " << endl;
    print(testgraph_dt);

    /* count vertices and edges */
    cout << "\n    2. COUNT: " << endl;
    cout << "Number of vertices = " << count_vertices(testgraph_dt) << endl;
    cout << "Number of edges    = " << count_edges(testgraph_dt) << endl;

    /* check reachability from top */
    cout << "\n    3. REACHABLE FROM TOP: " << endl;
    auto vtop = top(testgraph_dt);
    if (vtop) {
        cout << "Top vertex (i.e. root): " << vtop->to_string() << endl;
        if (DFS.reachable_from_vertex(testgraph_dt.base(), vtop))
            cout << "Every node is reachable from root, as expected." << endl;
        else
            cout << "ERROR: Graph is not connected." << endl;
    } else {
        cout << "ERROR: Root is NULL." << endl;
        return Failure;
    }

    /* find cycles */
    cout << "\n    4. FIND CYCLES: " << endl;
    DFS.dfs(testgraph_dt.base(), vtop);
    if (DFS.is_cyclic()) {
        cout << "Error: " << std::to_string(DFS.num_cycles()) << " cycle(s) found:" << endl;
        for (auto cp : DFS.get_cycles()) {
            cout << "Cycle #" << std::to_string(cp.first) << ": ";
            for (auto v : cp.second)
                cout << v->to_string() << "  ";
            cout << endl;
        }
        return Failure;
    } else
        cout << "No cycles found; tree is acyclic as expected";

    /* list vertices and edges in descending order of values */
    cout << "\n    5. ORDER BY VALUE: " << endl;
    cout << "List of vertices: " << endl;
    auto vertices_ordered = order_vertices_by_value(testgraph_dt, true);
    int c = 0;
    for (auto vo : vertices_ordered) {
        cout << vo->to_string() << "  ";
        if (++c % 9 == 0)
            cout << endl;
    }
    cout << "List of edges: " << endl;
    auto edges_ordered = order_edges_by_value(testgraph_dt, true);
    c = 0;
    for (auto eo : edges_ordered) {
        cout << eo->to_string() << "  ";
        if (++c % 3 == 0)
            cout << endl;
    }
    cout << endl;

    /* add edge */
    cout << "\n    6. ADD EDGE: " << endl;
    cout << "Trying to add edge that causes cycle: " << all_edges["ib"]->to_string() << " ..." << endl;
    if (add_edge(testgraph_dt, all_edges["ib"]) == Success) {
        cout << "ERROR: added invalid edge. New tree:" << endl;
        print(testgraph_dt);
        return Failure;
    } else {
        cout << "Operation FAILED, as expected." << endl;
    }

    cout << "Trying to add edge that violates connectivity: " << all_edges["jk"]->to_string() << " ..." << endl;
    if (add_edge(testgraph_dt, all_edges["jk"]) == Success) {
        cout << "ERROR: added invalid edge. New graph:" << endl;
        print(testgraph_dt);
        return Failure;
    } else {
        cout << "Operation FAILED, as expected." << endl;
    }

    cout << "Trying to add edge that violates one-parent rule: " << all_edges["bg"]->to_string() << " ..." << endl;
    if (add_edge(testgraph_dt, all_edges["bg"]) == Success) {
        cout << "ERROR: added invalid edge. New graph:" << endl;
        print(testgraph_dt);
        return Failure;
    } else {
        cout << "Operation FAILED, as expected." << endl;
    }

    /* remove edge */
    cout << "\n    7. REMOVE EDGE: " << endl;
    cout << "Trying to remove edge that breaks connectivity: " << all_edges["fg"]->to_string() << " ..." << endl;
    if (remove_edge(testgraph_dt, all_edges["fg"])) {
        cout << "ERROR: removed edge breaks connectivity. New graph:" << endl;
        print(testgraph_dt);
        return Failure;
    } else {
        cout << "Operation FAILED, as expected." << endl;
    }

    return Success;
}

int main(int argc, char* argv[])
{
    generate_all_vertices();
    cout << "All " << all_vertices.size() << " vertices generated ..." << endl;
    cout << "One instance, Vertex \"a\": " << all_vertices["a"]->to_string() << endl;
    // int c = 0;
    // for (auto va : all_vertices) {
    //     cout << va.second->to_string() << " ";
    //     if (++c % 9 == 0)
    //         cout << endl;
    // }

    generate_all_edges();
    cout << "All " << all_edges.size() << " edges generated ..." << endl;
    cout << "One instance, Directed Edge \"ab\": " << all_edges["ab"]->to_string() << endl;
    // c = 0;
    // for (auto ea : all_edges) {
    //     cout << ea.second->to_string() << " ";
    //     if (++c % 3 == 0)
    //         cout << endl;
    // }

    if (test_directed_graph() != Success)
        cout << "\n!!!TEST FAILED." << endl;

    if (test_directed_acyclic_graph() != Success)
        cout << "\n!!!TEST FAILED." << endl;

    if (test_directed_tree() != Success)
        cout << "\n!!!TEST FAILED." << endl;

    cout << "\n\n ... DONE" << endl;

    return 0;
}