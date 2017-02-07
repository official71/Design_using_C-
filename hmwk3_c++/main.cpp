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

template<typename Con, typename Ele>
void insert_to_seq(Con& to, vector<Ele>& from)
{
    for (auto i:from) {
        /* 
         * Bianry search for the index of insertion point
         */
        //auto indx = binary_search_in_seq(to, i, to.begin(), to.end());
        /* 
         * or,
         * Linear search for the index of insertion point
         */
        auto indx = linear_search_in_seq(to, i, to.begin(), to.end());
        to.insert(indx, i);
    }
}

template<typename Ele>
void insert_to_set(set<Ele>& to, vector<Ele>& from)
{
    for (Ele i:from)
        to.insert(i);
}

template<typename Con>
void remove_from_seq(Con& from, vector<int>& index)
{
    for (int i:index) {
        auto it = from.begin();
        for (int c = 0; c < i; c++)
            it++;
        from.erase(it);
    }
}

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
#if 0
    for (auto i = v.begin(); i < v.begin()+10; i++)
        cout << *i << endl;
#endif

    vector<int> rm_index {};
    gen_random_index(rm_index, max, rng);
#if 0
    for (auto i = rm_index.begin(); i < rm_index.end(); i++)
        cout << *i << endl;
#endif
    cout << time_stamp(t) << ",";

    /**********
     * Vector *
     **********/
    vector<int> vec {};
    insert_to_seq(vec, v);
#if 0
    for (auto i = vec.begin(); i != vec.end(); i++)
        cout << *i << endl;
#endif
    cout << time_stamp(t) << ",";

    remove_from_seq(vec, rm_index);
#if 0
    cout << "empty: " << vec.empty() << endl;
#endif
    cout << time_stamp(t) << ",";
 
    /********
     * List *
     ********/
    list<int> lst {};
    insert_to_seq(lst, v);
#if 0
    for (auto i = lst.begin(); i != lst.end(); i++)
        cout << *i << endl;
#endif
    cout << time_stamp(t) << ",";

    remove_from_seq(lst, rm_index);
#if 0
    cout << "empty: " << lst.empty() << endl;
#endif
    cout << time_stamp(t) << ",";

    /*******
     * Set *
     *******/
    set<int> st {};
    insert_to_set(st, v);
#if 0
    for (auto i = st.begin(); i != st.end(); i++)
        cout << *i << endl;
#endif
    cout << time_stamp(t) << ",";
 
    remove_from_seq(st, rm_index);
#if 0
    cout << "empty: " << st.empty() << endl;
#endif
    cout << time_stamp(t) << endl;
}

int main(int argc, char* argv[])
{
    /* specified maximum number, single-time mode */
    if (argc > 1) {
        run(atoi(argv[1]));
        return 0;
    }

    cout << "size,prepare,vect-in,vect-out,list-in,list-out\n";
    vector<int> vmax {10, 500, 2000, 10000, 50000, 100000, 200000};
    //vector<int> vmax {10, 500, 2000};
    constexpr int rep = 3;

    for (auto m:vmax) {
        for (auto i = 0; i < rep; i++)
            run(m);
    }

    return 0;
}
