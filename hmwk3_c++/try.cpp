#include <iostream>
#include <vector>
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

vector<int>::iterator get_index_in_vector(int val, vector<int>& vec,
    vector<int>::iterator beg, vector<int>::iterator end)
{
    if (beg == end)
        return beg;

    vector<int>::iterator i = beg;
    advance(i, distance(beg, end)/2);
    if (*i > val)
        return get_index_in_vector(val, vec, beg, i);
    else if (*i < val)
        return get_index_in_vector(val, vec, ++i, end);

    cout << "Fatal error: " << val << " is duplicate!" << endl;
    return beg;
}

void insert_seq_to_vector(vector<int>& from, vector<int>& to)
{
    for (auto i:from) {
        auto indx = get_index_in_vector(i, to, to.begin(), to.end());
        to.insert(indx, i);
    }
}

void remove_from_vector(vector<int>& from, vector<int>& index)
{
    for (int i:index)
        from.erase(from.begin() + i);
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

    vector<int> vec {};
    insert_seq_to_vector(v, vec);
    /* print some
	for (auto i = vec.begin(); i < vec.begin()+10; i++)
		cout << *i << endl;
    */
    auto t2 = high_resolution_clock::now();

    remove_from_vector(vec, rm_index);
    //cout << "empty: " << vec.empty() << endl;
    auto t3 = high_resolution_clock::now();

    /* let's count time! */
    cout << "-----------------------------" << endl;
    cout << "Preparation time: " << duration_cast<milliseconds>(t1-t0).count() << "msec" << endl;
    cout << "Insertion time: " << duration_cast<milliseconds>(t2-t1).count() << "msec" << endl;
    cout << "Deletion time: " << duration_cast<milliseconds>(t3-t2).count() << "msec" << endl;
}

int main()
{
    constexpr int max = 200000;

    for (auto i = 0; i < 3; i++)
        run(max);

    return 0;
}
