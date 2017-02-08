#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <random>
#include <chrono>
#include <functional>
#include <algorithm>

using namespace std;

void gen_random_seq(vector<int>& vec, int max, mt19937& g)
{
    for (int i = 1; i <= max; i++)
        vec.push_back(i);
    shuffle(vec.begin(), vec.end(), g);
}

void gen_random_index(vector<int>& vec, int max, mt19937& g)
{
    for (int i = max-1; i >= 0; i--) {
        auto die = bind(uniform_int_distribution<>{0,i}, g);
        vec.push_back(die());
    }
}

template<typename T>
int time_stamp(T& orig)
{
    auto t = chrono::high_resolution_clock::now();
    auto r = chrono::duration_cast<chrono::milliseconds>(t - orig).count();
    orig = t;

    return r;
}

/* Binary search for the insertion point in sequence */
template<typename Con, typename Ele, typename Ite>
Ite binary_search_in_seq(Con& seq, Ele val, Ite beg, Ite end)
{
    if (beg == end)
        return beg;

    Ite i = beg;
    for (int c = 0; c < distance(beg, end)/2; c++)
        i++;
    if (*i > val)
        return binary_search_in_seq(seq, val, beg, i);
    else if (*i < val)
        return binary_search_in_seq(seq, val, ++i, end);

    cout << "Fatal error: " << val << " is duplicate!\n";
    return beg;
}

/* Linear search for the insertion point in sequence */
template<typename Con, typename Ele, typename Ite>
Ite linear_search_in_seq(Con& seq, Ele val, Ite beg, Ite end)
{
    auto i = beg;
    for (; i != end; i++) {
        if (*i >= val)
            break;
    }
    return i;
}

struct Greater_than {
    int val;
    Greater_than(int v):val(v) {}
    bool operator()(const int& i) {return i>val;}
};

/* INSERTION (for std::vector and std::list) */
template<typename Con, typename Ele>
void insert_to_seq(Con& to, vector<Ele>& from)
{
    for (auto i:from) {
        /* 
         * 1. Linear search for the index of insertion point
         */
        auto indx = linear_search_in_seq(to, i, to.begin(), to.end());

        /* 
         * 2. Bianry search for the index of insertion point
         */
        //auto indx = binary_search_in_seq(to, i, to.begin(), to.end());

        /* 
         * 3. Using find_if and Lambda function
         */
        //auto indx = find_if(to.begin(), to.end(), [i](const int& v) {return v>i;});

        /* 
         * 4. Using find_if and function object
         */
        //auto indx = find_if(to.begin(), to.end(), Greater_than{i});

        to.insert(indx, i);
    }
}

template<typename Ele, typename Con>
void vector_insert_then_sort(vector<Ele>& to, Con& from)
{
    for (auto i:from) {
        to.push_back(i);
        sort(to.begin(), to.end());
    }
}

template<typename Ele, typename Con>
void list_insert_then_sort(list<Ele>& to, Con& from)
{
    for (auto i:from) {
        to.push_back(i);
        to.sort();
    }
}

/* INSERTION (for std::set) */
template<typename Ele>
void insert_to_set(set<Ele>& to, vector<Ele>& from)
{
    for (Ele i:from)
        to.insert(i);
}

/* DELETION */
template<typename Con>
void remove_from_seq(Con& from, vector<int>& index)
{
    for (int i:index) {
        auto it = from.begin();
        /* 1. explicit loop */
        for (int c = 0; c < i; c++)
            it++;

        /* 2. std::advance() */
        //advance(it, i);

        from.erase(it);
    }
}

/*
 * Single run
 * Input: (int)max, maximum integer, i.e. size
 */
void run(int max)
{
    cout << max << ",";

    /****************
     * Preparations *
     ****************/
    random_device rd;
    mt19937 rng(rd());

    /* generate the random sequence(vector) */
    auto t = chrono::high_resolution_clock::now();
    vector<int> v {};
    gen_random_seq(v, max, rng);

    /* generate the random deletion sequence */
    vector<int> rm_index {};
    gen_random_index(rm_index, max, rng);
    cout << time_stamp(t) << ",";


    /***************
     * std::vector *
     ***************/
    vector<int> vec;
    
    insert_to_seq(vec, v);
    //vector_insert_then_sort(vec, v);
    cout << time_stamp(t) << ",";

    remove_from_seq(vec, rm_index);
    cout << time_stamp(t) << ",";
 

    /*************
     * std::list *
     *************/
    list<int> lst;
    
    insert_to_seq(lst, v);
    //list_insert_then_sort(lst, v);
    cout << time_stamp(t) << ",";

    remove_from_seq(lst, rm_index);
    cout << time_stamp(t) << ",";


    /************
     * std::set *
     ************/
    set<int> st;

    insert_to_set(st, v);
    cout << time_stamp(t) << ",";
 
    remove_from_seq(st, rm_index);
    cout << time_stamp(t) << endl;
}


/****************************************
 <<<<<<<<<<<<<<   MAIN  >>>>>>>>>>>>>>>>
****************************************/
int main(int argc, char* argv[])
{
    /* specified maximum number, single-time mode */
    if (argc > 1) {
        run(atoi(argv[1]));
        return 0;
    }

    cout << "size,prepare,vect-in,vect-out,list-in,list-out,set-in,set-out\n";
    vector<int> vmax {10, 500, 2000, 10000, 50000, 100000, 200000};
    constexpr int rep = 3;

    for (auto m:vmax) {
        for (auto i = 0; i < rep; i++)
            run(m);
    }

    return 0;
}
