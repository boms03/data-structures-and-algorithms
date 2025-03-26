#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

int n,k,ans;
vector<int>v[101];
int visited[101];
void bfs(){
    queue<int>q;
    q.push(1);
    visited[1]=1;
    while(!q.empty()){
        int now = q.front();
        q.pop();
        for(int i=0;i<v[now].size();i++){
            int next = v[now][i];
            if(visited[next]) continue;
            q.push(next);
            ans++;
            visited[next]=1;
        }
    }
}
int main(){
    cin >> n;
    cin >> k;
    for(int i=0;i<k;i++){
        int a,b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    bfs();
    cout << ans << endl;
}

/*
    approach:
        basic bfs problem
        bfs starting from 1 and count the number of visited node
    
    O(N+K) using adjacency list
*/