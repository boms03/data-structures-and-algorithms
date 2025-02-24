#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
using namespace std;
typedef pair<double, double> pdd;
typedef pair<double,int> pdi;

int n;
vector<pdd>coordinates;
vector<vector<pair<double,int>>>edges;
double dist[103];

void dijkstra(int start){
    fill(dist, dist + 103, -1.0);
    priority_queue<pdi,vector<pdi>,greater<pdi>> pq;
    pq.push({0,start});
    while(!pq.empty()){
        pdi cur = pq.top();
        int cur_idx = cur.second;
        double cur_distance = cur.first;
        pq.pop();
        for(int i=0; i<edges[cur_idx].size();i++){
            double next_distance = edges[cur_idx][i].first;
            int next_idx = edges[cur_idx][i].second;
            if(dist[next_idx]==-1 || cur_distance+next_distance < dist[next_idx]){
                dist[next_idx] = cur_distance+next_distance;
                pq.push({dist[next_idx],next_idx});
            }
        }
    }
}
double getDistance(pdd a, pdd b){
    return sqrt(pow(a.first-b.first,2)+pow(a.second-b.second,2));
}
int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    for(int i=0;i<2;i++){
        double x,y;
        cin >> x >> y;
        coordinates.push_back({x,y});
    }
    cin >> n;
    for(int i=0;i<n;i++){
        double x,y;
        cin >> x >> y;
        coordinates.push_back({x,y});
    }
    edges.resize(n+3);
    for(int i=0;i<n+2;i++){
        for(int j=0;j<n+2;j++){
            if(i==j) continue;
            double distance = getDistance(coordinates[i],coordinates[j]);
            double walk_time = distance/5;
            double canon_time = 2 + abs(distance-50)/5;
            if(i==0 || i==1){
                edges[i].push_back({walk_time,j});
            } else{
                edges[i].push_back({min(canon_time,walk_time),j});
            }
        }
    }
    dijkstra(0);
    cout << dist[1] << '\n';
}