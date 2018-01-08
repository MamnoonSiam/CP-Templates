#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<
	T,
	null_type,
	less<T>, // use less_equal to use as multiset without erase operation
	rb_tree_tag,
	tree_order_statistics_node_update>;

// gives the number of keys with value strictly less than x
#define lesscount(x) order_of_key(x)
// gives the iterator to kth element (starting from 0)
#define kthiterator(x) find_by_order(x)

// A PATRICIA trie with a prefix-search node-updator type. Note that
// since the node updator is trie_prefix_search_node_update, then the
// container includes its method prefix_range.

typedef trie<
	string,
	null_type,
	trie_string_access_traits<>,
	pat_trie_tag,
	trie_prefix_search_node_update>
stl_trie;

// The following helper function takes a trie object and r_key, a
// const reference to a string, and prints all entries whose key
// includes r_key as a prefix.
void print_prefix_match(const stl_trie& t, const string& key)
{
	cout << "All keys whose prefix matches \"" << key << "\":" << endl;
	const auto match_range = t.prefix_range(key);
	for (auto it = match_range.first; it != match_range.second; ++it)
		cout << *it << ' ';
	cout << endl;
}

int main()
{
	stl_trie t;
	// Insert some entries.
	assert(t.insert("I").second == true);
	assert(t.insert("wish").second == true);
	assert(t.insert("that").second == true);
	assert(t.insert("I").second == false);
	assert(t.insert("could").second == true);
	assert(t.insert("ever").second == true);
	assert(t.insert("see").second == true);
	assert(t.insert("a").second == true);
	assert(t.insert("poem").second == true);
	assert(t.insert("lovely").second == true);
	assert(t.insert("as").second == true);
	assert(t.insert("a").second == false);
	assert(t.insert("trie").second == true);
	// Now search for prefixes.
	// Prints in lexicographical order :)
	print_prefix_match(t, "");
	print_prefix_match(t, "a");
	print_prefix_match(t, "as");
	print_prefix_match(t, "ad");
	print_prefix_match(t, "t");
	print_prefix_match(t, "tr");
	print_prefix_match(t, "trie");
	print_prefix_match(t, "zzz");
	return 0;
}

/*
Output:
All keys whose prefix matches "":
I a as could ever lovely poem see that trie wish 
All keys whose prefix matches "a":
a as 
All keys whose prefix matches "as":
as 
All keys whose prefix matches "ad":

All keys whose prefix matches "t":
that trie 
All keys whose prefix matches "tr":
trie 
All keys whose prefix matches "trie":
trie 
All keys whose prefix matches "zzz":

*/
