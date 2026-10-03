/**
 * Author: Roman Pervutinskiy
 * Description: Policy-based data structures from GCC.
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

gp_hash_table<T, U>;
cc_hash_table<T, U>;
