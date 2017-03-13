#ifndef _BASIC_H
#define _BASIC_H

#include <iostream>
#include <string>

using namespace std;


enum Retval {Success, Failure};


#ifdef DEBUG
void _log() {}
template<typename Head, typename ...Rest>
void _log(Head && h, Rest && ...r)
{
    std::cout << std::forward<Head>(h);
    _log(std::forward<Rest>(r)...);
}
#define _DEBUG(...) do\
{\
    std::cout << "[ " << __FILE__;\
    std::cout << " -> " << __FUNCTION__;\
    std::cout << " -> " << __LINE__ << " ] ";\
    _log(__VA_ARGS__);\
    std::cout << endl;\
} while(0)
#else
#define _DEBUG(...) do{} while(0)
#endif



typedef pair<string,int> Val;



struct vertex 
{
    Val val;
    
    vertex(void) { val = make_pair("NULL", -1); }
    vertex(Val v) { val = v; }

    bool operator< (const vertex& rhs) const
    {
        return val.second < rhs.val.second;
    }

    Val value(void) { return val; }
    void set_value(Val v) { val = v; }

    string to_string(void) 
    {
        return "[(" + get<0>(val) + ")::(" + std::to_string(get<1>(val)) + ")]";
    }
};

typedef shared_ptr<vertex> Vertex_ptr;


struct directed_edge 
{
    Val val;
    Vertex_ptr v_from, v_to;

    directed_edge(void) 
    {
        val = make_pair("NULL-->NULL", -1);
    }
    directed_edge(Vertex_ptr from, Vertex_ptr to, int v=-1) 
    {
        v_from = from;
        v_to = to;
        val = make_pair(from->to_string() + "-->" + to->to_string(), v);
    }
    directed_edge(Vertex_ptr from, Vertex_ptr to, Val v) 
    {
        v_from = from;
        v_to = to;
        val = v;
    }

    bool operator< (const vertex& rhs) const
    {
        return val.second < rhs.val.second;
    }

    bool contain(Vertex_ptr vp) { return v_from == vp || v_to == vp; }
    bool is_from(Vertex_ptr vp) { return v_from == vp; }
    bool is_to(Vertex_ptr vp) { return v_to == vp; }

    Vertex_ptr from(void) { return v_from; }
    Vertex_ptr to(void) { return v_to; }

    Val value(void) { return val; }
    void set_value(Val v) { val = v; }

    string to_string(void) 
    {
        return "{(" + get<0>(val) + ")::(" + std::to_string(get<1>(val)) + ")}";
    }
};



typedef shared_ptr<directed_edge> Edge_ptr;



typedef std::set<Vertex_ptr> Graph_vertices;
typedef std::set<Edge_ptr> Set_edges;
typedef std::map<Vertex_ptr, std::set<Edge_ptr>> Graph_edges;


inline bool operator< (const Vertex_ptr lvp, const Vertex_ptr rvp) 
{
    return get<1>(lvp->value()) < get<1>(rvp->value());
}
inline bool operator< (const Edge_ptr lep, const Edge_ptr rep) 
{
    return get<1>(lep->value()) < get<1>(rep->value());
}


class depth_first_search;

struct base_graph 
{
    Graph_vertices vertices;
    Graph_edges edges_from; /* mapping vertex A and all edges A --> ?? */
    Graph_edges edges_to;   /* mapping vertex A and all edges ?? --> A */

    base_graph() {}
    base_graph(vector<Vertex_ptr>& vv);
    base_graph(vector<Edge_ptr>& ve);
    base_graph(vector<Vertex_ptr>& vv, vector<Edge_ptr>& ve);

    bool vertex_in_graph(Vertex_ptr x)
    {
        return vertices.find(x) != vertices.end();
    }
    bool edge_in_graph(Edge_ptr e)
    {
        auto f = e->from();
        auto search = edges_from.find(f);
        if (search == edges_from.end())
            return false;
        return search->second.find(e) != search->second.end();
    }

    void vertices_insert(Vertex_ptr v) { vertices.insert(v); }
    void vertices_erase(Vertex_ptr v) { vertices.erase(v); }

    void edges_from_insert(Vertex_ptr f, Edge_ptr e)
    {
        auto search = edges_from.find(f);
        if (search == edges_from.end())
            edges_from.insert(make_pair(f, Set_edges{e}));
        else
            search->second.insert(e);
    }
    void edges_to_insert(Vertex_ptr t, Edge_ptr e)
    {
        auto search = edges_to.find(t);
        if (search == edges_to.end())
            edges_to.insert(make_pair(t, Set_edges{e}));
        else
            search->second.insert(e);
    }
    void edges_vector_insert(vector<Edge_ptr>& ve)
    {
        for (auto e : ve) {
            if (e) {
                auto f = e->from();
                auto t = e->to();
                if (f && t) {
                    edges_from_insert(f, e);
                    edges_to_insert(t, e);
                    vertices_insert(f);
                    vertices_insert(t);
                }
            }
        }
    }

    Vertex_ptr vertices_find_by_value(Val val)
    {
        for (auto p : vertices) {
            if (val == p->value()) 
                return p;
        }
        return NULL;
    }

    Edge_ptr edges_find_by_value(Val val)
    {
        for (auto p : edges_from) {
            for (auto q : p.second) {
                if (val == q->value()) 
                    return q;
            }
        }
        return NULL;
    }

    Edge_ptr edges_from_find(Vertex_ptr f, Vertex_ptr t)
    {
        Edge_ptr ptr = NULL;

        auto search = edges_from.find(f);
        if (search == edges_from.end())
            return NULL;
        
        for (auto p : search->second) {
            if (p->to() == t) {
                ptr = p;
                break;
            }
        }
        return ptr;
    }
    Edge_ptr edges_to_find(Vertex_ptr f, Vertex_ptr t)
    {
        Edge_ptr ptr = NULL;

        auto search = edges_to.find(f);
        if (search == edges_to.end())
            return NULL;
        
        for (auto p : search->second) {
            if (p->to() == t) {
                ptr = p;
                break;
            }
        }
        return ptr;
    }

    Graph_vertices edges_from_neighbors(Vertex_ptr f)
    {
        Graph_vertices rv {};

        auto search = edges_from.find(f);
        if (search == edges_from.end())
            return rv;

        for (auto e : search->second)
            rv.insert(e->to());
        return rv;
    }

    Graph_vertices edges_to_neighbors(Vertex_ptr t)
    {
        Graph_vertices rv {};

        auto search = edges_to.find(t);
        if (search == edges_to.end())
            return rv;

        for (auto e : search->second)
            rv.insert(e->from());
        return rv;
    }

    void edges_from_erase(Vertex_ptr f, Edge_ptr e)
    {
        auto search = edges_from.find(f);
        if (search != edges_from.end())
            search->second.erase(e);
    }
    void edges_to_erase(Vertex_ptr t, Edge_ptr e)
    {
        auto search = edges_to.find(t);
        if (search != edges_to.end())
            search->second.erase(e);
    }

    void edges_from_to_erase(Vertex_ptr f, Vertex_ptr t)
    {
        Edge_ptr e = edges_from_find(f, t);
        if (!e)
            e = edges_to_find(f, t);
        if (!e)
            return;

        edges_from_erase(f, e);
        edges_to_erase(t, e);
    }

    string vertices_to_string(void)
    {
        string s = "";
        int c = 0;
        for (auto v : vertices) {
            s += v->to_string() + "  ";
            if (++c % 9 == 0)
                s += "\n";
        }
        return s;
    }

    string edges_to_string(Graph_edges& ge)
    {
        string s = "";
        int c = 0;
        for (auto em : ge) {
            for (auto e : em.second) {
                s += e->to_string() + "  ";
                if (++c % 3 == 0)
                    s += "\n";
            }
        }
        return s;
    }
};

base_graph::base_graph(vector<Vertex_ptr>& vv) 
{
    for (auto v : vv) {
        if (v)
            vertices_insert(v);
    }
}
base_graph::base_graph(vector<Edge_ptr>& ve)
{
    for (auto e : ve) {
        if (e) {
            auto f = e->from();
            auto t = e->to();
            if (f && t) {
                edges_from_insert(f, e);
                edges_to_insert(t, e);
                vertices_insert(f);
                vertices_insert(t);
            }
        }
    }
}
base_graph::base_graph(vector<Vertex_ptr>& vv, vector<Edge_ptr>& ve)
{
    for (auto e : ve) {
        if (e) {
            auto f = e->from();
            auto t = e->to();
            if (f && t) {
                edges_from_insert(f, e);
                edges_to_insert(t, e);
                vertices_insert(f);
                vertices_insert(t);
            }
        }
    }
    for (auto v : vv) {
        if (v)
            vertices_insert(v);
    }
}

#endif