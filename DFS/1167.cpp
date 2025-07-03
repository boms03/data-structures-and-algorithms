// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#define pii pair<int,int>
using namespace std;

int v, max_dist,max_point;
vector<vector<pii>>infos;
bool visited[10000001];

void dfs(int cur_vertex,int dist){
    //cout << cur_vertex << endl;
    if(visited[cur_vertex]) return;
    visited[cur_vertex]=true;
    
    if(dist >= max_dist){
        max_dist = dist;
        max_point= cur_vertex;
    }
    for(int i=0;i<infos[cur_vertex].size();i++){
        dfs(infos[cur_vertex][i].first, dist + infos[cur_vertex][i].second);
    }
}
int main() {
    cin >> v;
    infos.resize(v+1);
    for(int i=0;i<v;i++){
        int vertex_from, vertex_to, cost;
        cin >> vertex_from;
        while(cin >> vertex_to){
            if(vertex_to==-1) break;
            cin >> cost; 
            infos[vertex_from].push_back({vertex_to,cost});
        }
    }
    
    dfs(1,0);
    //cout << max_point << " " << max_dist << endl;
    memset(visited,false,sizeof(visited));
    dfs(max_point,0);
    cout << max_dist;
    return 0;
}
