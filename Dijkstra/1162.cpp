#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;
int N,M,K,a,b,c;
vector<pair<long long,pair<int,int>>>adj[100001]; // vector<time,{c,b}  use long long type for time <= 1,000,000
long long dist[10001][21]; // time is long long type so as dist

void dijkstra(){
     for(int i=1; i<=N; i++){
        for(int j=0; j<=K; j++){
           dist[i][j]=LLONG_MAX;
        }
     }

    priority_queue< pair<long long,pair<int,int>> >pq;
    dist[1][0]=0;
    pq.push({0,{1,0}});

    while(!pq.empty()){
        long long d = -pq.top().first;
        int x = pq.top().second.first;
        int k = pq.top().second.second; // number of combined roads
        pq.pop();

        if(x==N) break; // target found
        if(dist[x][k] < d) continue; // skip if already updated to shorter time

        for(int i=0; i<adj[x].size();i++){
            long long nd = d + adj[x][i].first;
            int nx = adj[x][i].second.first;

            if (nd<dist[nx][k]){  // not combining roads
                dist[nx][k]=nd;
                pq.push({-nd,{nx,k}});
            }

            if (d<dist[nx][k+1] && k+1<=K){ // k+1: nx takes same time as x
                dist[nx][k+1]=d;
                pq.push({-d,{nx,k+1}});
            }
        }
    }
}
int main(){
    cin >> N >> M >> K;
    while(M--){
        cin >> a >> b >> c;
        adj[a].push_back({c,{b,0}});
        adj[b].push_back({c,{a,0}});
    }
    dijkstra();

    long long ans = LLONG_MAX;
    for(int i=0; i<=K; i++) ans=min(ans, dist[N][i]);
    cout << ans << endl;
}

/*
    number of vertex: N*K
    number of edge: M*K
    O(MKlog_2 N*K)
*/



