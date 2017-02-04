#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

template<typename Con, typename Ele>
void insert_to_seq(Con& to, vector<Ele>& from)
{
    for (auto i:from) {
        auto indx = binary_search_in_seq(to, i, to.begin(), to.end());
        to.insert(indx, i);
    }
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
    random_device rd;
    mt19937 rng(rd());

    /* generate the random sequence(vector) */
    auto t0 = high_resolution_clock::now();
    vector<int> v {};
    gen_random_seq(v, max, rng);
    /* print some
    for (auto i = v.begin(); i < v.begin()+10; i++)
        cout << *i << endl;
    */

    vector<int> rm_index {};
    gen_random_index(rm_index, max, rng);
    /* print some
    for (auto i = rm_index.begin(); i < rm_index.end(); i++)
        cout << *i << endl;
    */
    auto t1 = high_resolution_clock::now();
    cout << "-----------------------------" << endl;
    cout << "Preparation time: " << duration_cast<milliseconds>(t1-t0).count() << "msec" << endl;

    vector<int> vec {};
    insert_to_seq(vec, v);
    /* print some
    for (auto i = vec.begin(); i != vec.end(); i++)
        cout << *i << endl;
    */
    t0 = t1;
    t1 = high_resolution_clock::now();
    cout << "Vector insertion time: " << duration_cast<milliseconds>(t1-t0).count() << "msec" << endl;

    remove_from_seq(vec, rm_index);
    //cout << "empty: " << vec.empty() << endl;
    t0 = t1;
    t1 = high_resolution_clock::now();
    cout << "Vector deletion time: " << duration_cast<milliseconds>(t1-t0).count() << "msec" << endl;
    
    list<int> lst {};
    insert_to_seq(lst, v);
    /* print some
    for (auto i = lst.begin(); i != lst.end(); i++)
        cout << *i << endl;
    */
    t0 = t1;
    t1 = high_resolution_clock::now();
    cout << "List insertion time: " << duration_cast<milliseconds>(t1-t0).count() << "msec" << endl;

    remove_from_seq(lst, rm_index);
    //cout << "empty: " << lst.empty() << endl;
    t0 = t1;
    t1 = high_resolution_clock::now();
    cout << "List deletion time: " << duration_cast<milliseconds>(t1-t0).count() << "msec" << endl;
    
    cout << "-----------------------------" << endl;
}

int main(int argc, char* argv[])
{
    int max = 50000;
    if (argc > 1)
        max = atoi(argv[1]);

    for (auto i = 0; i < 3; i++)
        run(max);

    return 0;
}
