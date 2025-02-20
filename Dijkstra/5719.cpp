#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<cstring>
using namespace std;
typedef pair<int, int> pii;
int n, m, s, d;
int dist[501];
bool deleted[501][501];
vector<vector<pii>>v;
vector<vector<int>>path;

void dijkstra() {
	priority_queue<pii, vector<pii>, greater<pii>>pq;
	fill(&dist[0], &dist[500], INT_MAX);
	bool visited[500] = { false, };
	pq.push({ 0, s });
	dist[s] = 0;
	visited[s] = true;
	while (!pq.empty()) {
		pii cur = pq.top();
		int cur_cost = cur.first;
		int cur_node = cur.second;
		visited[cur_node] = true;
		pq.pop();

		for (int i = 0; i < v[cur_node].size(); i++) {
			
			int next_cost = v[cur_node][i].second;
			int next_node = v[cur_node][i].first;

			if (visited[next_node]) continue;
			if (deleted[cur_node][next_node]) continue;

			if (dist[next_node] > cur_cost + next_cost) {
				path[next_node].clear();
				pq.push({ cur_cost + next_cost, next_node });
				path[next_node].push_back(cur_node);
				dist[next_node] = cur_cost + next_cost;
			}
			else if (dist[next_node] == cur_cost + next_cost) {
				path[next_node].push_back(cur_node);
			}
		}
	}
}

// 최단 경로가 여러개라면 bfs로 지우기
// 1 - 2 - (3or4) - 5 같은 경우 뒤에서부터 지우기
void delete_path() {
    bool visited[500] = { false, };
	  queue<int>q;
	  q.push(d);
	  visited[d] = true;
	  while (!q.empty()) {
		int to = q.front();
		q.pop();
		for (int i = 0; i < path[to].size(); i++) {
			int from = path[to][i];
			if(!visited[from]) q.push(from);
			deleted[from][to] = true;
			visited[from] = true;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		cin >> s >> d;

		v.assign(n + 1, vector<pii>());
		path.assign(n + 1, vector<int>());

		for (int i = 0; i < m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			v[a].push_back({ b,c });
		}

    fill(&deleted[0][0], &deleted[500][500], false);
        
    //O(elogv)
		dijkstra();
		
		//O(e+v)
		delete_path();
		
		//O(elogv)
		dijkstra();

		if (dist[d] == INT_MAX) cout << -1 << '\n';
		else cout << dist[d] << '\n';
	}

}