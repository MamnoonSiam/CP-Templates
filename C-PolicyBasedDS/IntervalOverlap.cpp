#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef int ui;
typedef pair< ui, ui> interval;
template<class CNI,
	 class NI,
	 class CpF,
	 class Allocator>
struct intervals_node_update {
public:
	typedef ui metadata_type;
	bool overlaps(const interval& r_interval) {
		CNI nit = node_begin();
		CNI end_it = node_end();
		while (nit != end_it) {
			if (r_interval.second >= (*nit)->first&&
		    	r_interval.first <= (*nit)->second) return true;
			CNI l_nd_it = nit.get_l_child();
			const ui lme =(l_nd_it == end_it) ? 0 : l_nd_it.get_metadata();
			if (lme >= r_interval.first) nit = l_nd_it;
			else nit = nit.get_r_child();
    	} return false;
	}
protected:
	inline void operator()(NI nit, CNI end_nd_it) {
		const ui lme =(nit.get_l_child() == end_nd_it)?
			0 : nit.get_l_child().get_metadata();
		const ui rme =(nit.get_r_child() == end_nd_it)?
			0 : nit.get_r_child().get_metadata();
    	const_cast<ui&>(nit.get_metadata()) =
			max((*nit)->second, max<ui>(lme, rme));
	}
	virtual CNI node_begin() const = 0;
	virtual CNI node_end() const = 0;
	virtual ~intervals_node_update() { }
};

template<class Cntnr>
void some_op_sequence(Cntnr r_c)
{
	r_c.insert(make_pair(0, 100));
	r_c.insert(make_pair(150, 160));
	r_c.insert(make_pair(300, 1000));
	r_c.insert(make_pair(10000, 100000));
	r_c.insert(make_pair(200, 100200));

	assert(r_c.overlaps(make_pair(145, 165)) == true);
	assert(r_c.overlaps(make_pair(145, 155)) == true);
	assert(r_c.overlaps(make_pair(165, 175)) == false);
	assert(r_c.overlaps(make_pair(100201, 100203)) == false);

	r_c.erase(make_pair(150, 160));

	assert(r_c.overlaps(make_pair(145, 165)) == false);
	assert(r_c.overlaps(make_pair(165, 175)) == false);
	assert(r_c.overlaps(make_pair(0, 300000)) == true);
}

int main()
{
	// Test a red-black tree.
	some_op_sequence(tree<
		   interval,
		   null_type,
		   less<interval>,
		   rb_tree_tag,
		   intervals_node_update>());

	// Test an ordered-vector tree.
	some_op_sequence(tree<
		   interval,
		   null_type,
		   less<interval>,
		   ov_tree_tag,
		   intervals_node_update>());

	// Test a splay tree.
	some_op_sequence(tree<
		   interval,
		   null_type,
		   less<interval>,
		   splay_tree_tag,
		   intervals_node_update>());
	
	return 0;
}
