#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

int n,m,f1,f2;
vector< pair<int,int> >v[10001];
int visited[10001];

bool bfs(int w){ // (2)
    queue<int>q;
    q.push(f1);
    visited[f1]=1;
    while(!q.empty()){
        int curFactory = q.front();
        q.pop();

        if (curFactory==f2) return true;
        for(int i=0;i<v[curFactory].size();i++){
            int nextFactory = v[curFactory][i].first;
            int nextFactoryCost = v[curFactory][i].second;
            if(nextFactoryCost>=w && !visited[nextFactory]){
                visited[nextFactory]=1;
                q.push(nextFactory);
            }
        }
    }
    return false;
}
int ps(int l,int r){ // (1)
    while(l<=r){
        memset(visited,0,sizeof(visited));
        int mid = (l+r)/2;
        if (bfs(mid)){
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return r;
}
int main(){
    cin >> n >> m;
    int a,b,c;
    int mn=1e9;
    int mx=0;
    for(int i=0;i<m;i++){
        cin >> a >> b >> c;
        v[a].push_back({b,c});
        v[b].push_back({a,c});
        if(c>mx) mx=c;
        if(c<mn) mn=c;
    }
    cin >> f1 >> f2;
    cout << ps(mn,mx) << endl;
    
}

/*
    Approach:
        Pick a possible maximum weight and check if the weight can be used to go from the starting factory to the ending factory.
        
        (1) Use parametric search to pick a weight.
        The starting range is from the minimum restricted weight and the maximum.
        Try larger weight (l=mid+1) if BFS(current weight) returns true;

        (2) Use BFS to check if the picked weight is possible

        (1)O(lgC) * (2)O(N+M)
        O(NlgC)
*/