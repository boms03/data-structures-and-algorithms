#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<climits>
using namespace std;
typedef pair<int,int> pii;

vector<vector<pii>> info;
vector<int>dist;
vector<vector<int>>parent;
bool check[501];

int n,m;

void dijkstra(int start, int end){
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,start});
    while(!pq.empty()){
        pii cur = pq.top();
        int cur_dist = cur.first;
        int cur_idx = cur.second;
        if (cur_idx==end) break;
        if (dist[cur_idx]<cur_dist) continue;
        pq.pop();
        for(int i=0;i<info[cur_idx].size();i++){
            pii next_info = info[cur_idx][i];
            int next_dist = next_info.second;
            int next_idx = next_info.first;
            if (next_dist == -1) continue;
            if(dist[next_idx] > cur_dist+next_dist){
                dist[next_idx] = cur_dist+next_dist;
                pq.push({dist[next_idx],next_idx});
                parent[next_idx].clear();
                parent[next_idx].push_back(cur_idx);
            } else if(dist[next_idx] == cur_dist+next_dist){
                parent[next_idx].push_back(cur_idx);
            }
        }
    }
}

void delete_cur(int from_idx, int to_idx){
    for (int i = 0; i < info[from_idx].size(); i++) {
        if (info[from_idx][i].first == to_idx){
            info[from_idx][i].second = -1;
            break;
        }
    }
}
void btk_remove(int destination){
    memset(check,false,sizeof(check));
    queue<int>q;
    q.push(destination);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        if(check[cur]) continue;
        check[cur] = true;
        for (int i=0;i<parent[cur].size();i++){
            delete_cur(parent[cur][i],cur);
            q.push(parent[cur][i]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while(cin >> n >> m){
        if(!n && !m) break;
        int s,d;
        cin >> s >> d;
        info.resize(n+1);
        parent.resize(n+1);
        dist.assign(n+1,INT_MAX);
        for(int i=0; i<m;i++){
            int a,b,c;
            cin >> a >> b >> c;
            info[a].push_back({b,c});
        }
        dijkstra(s,d);
        btk_remove(d);
        dist.assign(n+1,INT_MAX);
        dijkstra(s,d);
        if(dist[d]==INT_MAX) cout << -1 << '\n';
        else cout << dist[d] << '\n';

        info.clear();
        parent.clear();
    }

}