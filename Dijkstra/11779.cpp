#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
vector<pair<int,int>>adj[1001];
vector<int>ans;
int dist[1001];
int visit[1001];

int n,m,A,B,a,b,c,s,e;

void dijk(int s){
    fill(dist,dist+n+1,INT_MAX);
    priority_queue<pair<int,int>>pq;

    // initialize
    dist[s]=0;
    pq.push({0,s});

    while(!pq.empty()){
        int d = -pq.top().first;
        int x = pq.top().second;
        pq.pop();

        if(x==e) break; //break when target found 

        for (int i=0; i<adj[x].size(); i++){
            int nd = d + adj[x][i].first;
            int nx = adj[x][i].second;
            if (nd<dist[nx]){
                // memorize previous point
                visit[nx]=x;
                // update the shortest distance
                dist[nx]=nd;
                pq.push({-nd,nx});
            }
        }

    }
}

int main(){
    cin >> n;
    cin >> m;
    while(m--){
        cin >> a >> b >> c;
        adj[a].push_back({c,b});
    }
    cin >> s >> e;
    dijk(s);
    int t = e;
    while(t){
        ans.push_back(t);
        t = visit[t];
    }

    cout << dist[e] << "\n";
	cout << ans.size() << "\n";
	for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] << " ";

}

/*
    Approach:
        Use dijkstra algorithm to find the minimum cost to reach each node.
        Use visit array visit[next node]= current node to record the path that costs the least.

    Time Complexity:
        test all edges : O(e)
        inserting into a priority queue : O(loge)
        O(eloge)
*/