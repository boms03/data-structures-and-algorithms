#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <iostream>
#define pii pair<int,int>
using namespace std;

int parent[201];
vector<vector<pii>>adj_list;
int dist[201];

void dijkstra(int s){
    fill(dist,dist+201,INT_MAX);
    
    dist[s]=0;
    parent[s]=-1;
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    pq.push({0,s});
    while(!pq.empty()){
        pii cur = pq.top();
        int cost = cur.first;
        int node = cur.second;
        pq.pop();
    
        if(dist[node]<cost) continue;
        
        for(pii next_info: adj_list[node]){
            int next_cost = cost + next_info.first;
            int next_node = next_info.second;
            if(dist[next_node]>next_cost){
                //cout << node << " " << next_node << endl;
                dist[next_node]=next_cost;
                pq.push({next_cost,next_node});
                parent[next_node] = node;
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    adj_list.clear();
    adj_list.resize(n+1);
    for(vector<int> fare: fares){
        int c = fare[0];
        int d = fare[1];
        int f = fare[2];
        adj_list[c].push_back({f,d});
        adj_list[d].push_back({f,c});
    }
    dijkstra(s);
    int without_share = dist[a] + dist[b];
    int ans = without_share;
    for(int i=1;i<=n;i++){
        if(i==s)continue;
        dijkstra(i);
        int share = dist[s]+dist[a]+dist[b];
        ans = ans > share ? share : ans;
    }
    return ans;
}