#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int,int> pii;
int n,p,k;
int dist[1001];
vector<int>cost;
int path[1001];
vector<pii>edge[1001];

bool dijkstra(int value){
    for(int i=1;i<=n;i++){
        dist[i]=1e9;
    }
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    pq.push({0,1});
    dist[1]=0;
    while(!pq.empty()){
        int cCost = pq.top().first;
        int cNode = pq.top().second;
        pq.pop();

        if(dist[cNode]<cCost) continue;

        for(int i=0;i<edge[cNode].size();i++){
            int nNode = edge[cNode][i].first;
            int nCost = edge[cNode][i].second > value;

            if(nCost+cCost < dist[nNode]){
                dist[nNode] = nCost+cCost;
                pq.push({dist[nNode],nNode});
            }
        }
    }
    return dist[n]<=k;
}
int main(){
    cin >> n >> p >> k;

    for (int i=0;i<p;i++){
        int a,b,c;
        cin >> a >> b >> c;
        edge[a].push_back({b,c});
        edge[b].push_back({a,c});
    }

    int l = 0; // does not pay at all
    int r = 1e9;
    int ans = -1;
    while(l<=r){
        int mid = (l+r)/2;
        if(dijkstra(mid)){
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;

}

/*
    Approach:
        Use parametric search to decide the minimum payment.
        Use dijkstra to find cost from node 1 to node n.
        1] If a cost from node a to node b is larger than the minimum value from the parametric search, consider the cost as 1.
        2] Otherwise the cost is 0.
        3] By changing the cost, we can find how many edges should be bought to reach n from 1.
        [!] K edges are free so the minimum cost from node 1 to node n should be less or equal to K to minimize the payment.
        [!] The left boundary of parametric search should inlcude 0!! because it can be free if k is big enough
    Time Complexity:
        O(log1e9*PlogV)

*/