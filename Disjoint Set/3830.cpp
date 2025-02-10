#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

typedef pair<int, pair<int, int>> pipii;
int n, m;

int parent[100001];
long long weight[100001];

void init() {
	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}
}

int find(int x) {
    if (parent[x] == x) return x;
    int root = find(parent[x]);
    weight[x] += weight[parent[x]];
    return parent[x] = root;
}


void join(int a, int b, int w) {
	int a_root = find(a);
	int b_root = find(b);

	if (a_root == b_root) return;

    parent[b_root] = a_root;
    weight[b_root] = weight[a] - weight[b] + w;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		init();
		for (int i = 0; i < m; i++) {
			char q;
			int a, b, c;
			cin >> q;
			cin >> a >> b;
			if (q == '!') {
				cin >> c;
				if (a < b) {
					join(a, b, c);
				}
				else {
					join(b, a, -c);
				}
			}
			else {
				if (find(a) != find(b)) cout << "UNKNOWN" << '\n';
				else cout << weight[b] - weight[a] << '\n';
			}
		}
		memset(parent, 0, sizeof(parent));
		memset(weight, 0, sizeof(weight));
	}
}