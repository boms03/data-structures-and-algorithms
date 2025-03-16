#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

int N,E,ans,v1, v2;
vector<pair<int, int>> adj[810];
int dist[801];

void dijkstra(int start){
    fill(dist,dist+801,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >pq; // min heap
    pq.push({0,start});
    dist[start]=0;

    while(!pq.empty()){
        int d = pq.top().first; // current distance of the start
        int x = pq.top().second; // current point
        pq.pop();
        for (int i=0; i<adj[x].size(); i++){
            int nd = d + adj[x][i].first; // possible shortest distance to the next point
            int nx = adj[x][i].second; // next point
            if(nd<dist[nx]){
                dist[nx]=nd; // update shortest distance
                pq.push({nd,nx}); // min heap the updated shortest distance
            }
        }
    }
}

int main(){
    cin >> N >> E;
    for (int i=0;i<E;i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({c,b}); 
        adj[b].push_back({c,a}); // can pass already visited node == both way
    }
    cin >> v1 >> v2;
    dijkstra(1); // find the shortest distance from 1 to v1 and 1 to v2 

    int atov1= dist[v1];
    int atov2= dist[v2];

    dijkstra(v1); // find the shortest distance from v1 to v2
    int v1tov2= dist[v2]; // the shortest distance from v1 to v2 is the same as v2 to v1 in both way

    dijkstra(v2); // find the shortest distance from v2 to N
    int v2tob = dist[N];

    dijkstra(v1); // find the shortest distance from v1 to N
    int v1tob = dist[N];


    // true if any point is unreachable
    bool f = atov1==INT_MAX||v1tov2==INT_MAX||v2tob==INT_MAX;
    bool s = atov2==INT_MAX||v1tov2==INT_MAX||v1tob==INT_MAX;
    if (!f&&!s){
        cout << min(atov1+v1tov2+v2tob,atov2+v1tov2+v1tob) << endl;
    } else if (!f){
        cout << atov1+v1tov2+v2tob << endl;
    } else if (!s){
        cout << atov2+v1tov2+v1tob << endl;
    } else {
        cout << -1 << endl;
    }

}

/*
    O(Elog_2 N)
*/