#include<iostream>
#include<cmath>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
int n, l;

void init(int node, int s, int e, vector<long long>&seg_tree) {
	if (s == e) return;
	int mid = (s + e) >> 1;
	init(node * 2, s, mid,seg_tree);
	init(node * 2 + 1, mid + 1, e,seg_tree);
	seg_tree[node] = min(seg_tree[node * 2], seg_tree[node * 2 + 1]);
}

long long query_min(int node, int s, int e, int q_s, int q_e, vector<long long>&seg_tree) {
	if (q_e < s || q_s > e) return LLONG_MAX;
	if (q_s <= s && e <= q_e) {
		return seg_tree[node];
	}
	int mid = (s + e) >> 1;
	return min(query_min(node * 2, s, mid, q_s, q_e,seg_tree), query_min(node * 2+1, mid + 1, e, q_s, q_e,seg_tree));
}
int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

	cin >> n >> l;
	int tree_height = ceil(log2(n));
	int tree_size = 1 << (tree_height + 1);
	int start_index = tree_size >> 1;
    vector<long long>seg_tree(tree_size);

	for(int i=start_index;i<start_index + n;i++){
		cin >> seg_tree[i];
	}

	init(1, start_index, tree_size - 1, seg_tree);

	for (int i = 0; i < n; i++) {
		int s = max(0, i - l + 1);
		cout << query_min(1, start_index, tree_size - 1, s + start_index, i+start_index, seg_tree) << " ";
	}

}