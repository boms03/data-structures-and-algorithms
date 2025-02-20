#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<climits>
using namespace std;
typedef pair<int, int> pii;

int depth[100001];
bool visited[100001];
int parent[21][100001];
int min_road[21][100001];
int max_road[21][100001];
vector<vector<pii>>adj_lst;
int n, m, max_k;

void bfs() {
	queue<int>q;
	q.push(1);
	depth[1] = 1;
	visited[1] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < adj_lst[cur].size(); i++) {
			int next = adj_lst[cur][i].first;
            int weight = adj_lst[cur][i].second;
			if (visited[next]) continue;
			q.push(next);
			visited[next] = true;
			parent[0][next] = cur;
            min_road[0][next] = weight;
            max_road[0][next] = weight;
			depth[next] = depth[cur] + 1;
		}
	}
}

void update_parent() {
	for (int k = 1; k <= max_k; k++) {
		for (int j = 1; j<=n ; j++) {
			parent[k][j] = parent[k - 1][parent[k - 1][j]];
            min_road[k][j] = min(min_road[k-1][j], min_road[k-1][parent[k-1][j]]);
            max_road[k][j] = min(max_road[k-1][j], max_road[k-1][parent[k-1][j]]);
            parent[k][j] = parent[k - 1][parent[k - 1][j]];
		}
	}
}

int balance_depth(int a, int b)
{
	int diff = depth[a] - depth[b];
    int x = a;
	for(int k = max_k; k>=0; k--){
        if(diff & (1<<k)) x = parent[k][x];
    }
    return x;
}

pii lca(int a, int b) {
    int min_len = INT_MAX;
    int max_len = 0;
	for (int i = max_k; i >= 0; i--) {
		if (parent[i][a] != parent[i][b]) {
			a = parent[i][a];
			b = parent[i][b];
            min_len = min(min_len,min(min_road[i][a],min_road[i][b]));
            max_len = max(max_len,max(max_road[i][a],max_road[i][b]));
		}
	}
	return {min_len,max_len};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> n;
    max_k = ceil(log2(n));
	adj_lst.resize(n + 1);
	for (int i = 0; i < n-1; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		adj_lst[a].push_back({b,w});
		adj_lst[b].push_back({a,w});
	}
	bfs();
	update_parent();
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		if (depth[a] > depth[b]) {
			a= balance_depth(a, b);
		}
		else if (depth[a] < depth[b]) {
			b= balance_depth(b, a);
		}
        pii result = lca(a,b);
		cout << result.first << result.second << '\n';
	}
}