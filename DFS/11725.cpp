#include<iostream>
#include<vector>
using namespace std;

int n;
vector<int>v[100001];
int visited[100001];
int parent[100001];

void dfs(int s){
    visited[s]=1;
    for(int i=0;i<v[s].size();i++){
        if(!visited[v[s][i]]) {
            parent[v[s][i]]=s;
            dfs(v[s][i]);
        }
    }
}

int main(){
    cin >> n;
    for(int i=0;i<n-1;i++){
        int a,b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(1);
    for(int i=2;i<=n;i++){
        cout << parent[i] << '\n';
    }

}

/*
    Approach:
        Keep record of parent node before the recursion into the child node
    Time Complexity:
        O(V+E) = O(N+N-1) = O(N)
*/