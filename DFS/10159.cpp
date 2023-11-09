#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int n,m,cnt=0;
vector<int>up[101];
vector<int>down[101];
bool visited[101];

void dfs(vector<int>v[],int s){
    visited[s]=true;
    cnt++;
    for(int i=0;i<v[s].size();i++){
        if(!visited[v[s][i]]){
            dfs(v, v[s][i]);
        }
    }
}

int main(){
    cin >> n;
    cin >> m;
    for (int i=0;i<m;i++){
        int a,b;
        cin >> a >> b;
        up[a].push_back(b);
        down[b].push_back(a);
    }
    for (int i=1;i<=n;i++){
        dfs(up,i);
        memset(visited,false,sizeof(visited));
        dfs(down,i);
        cout << n-cnt+1<< '\n';
        memset(visited,false,sizeof(visited));
        cnt=0;
    }
}


/*
    Approach:
        To decide how many objects can be compared to a specific object, count heavier and lighter objects than the object.
        Subtracting the count from n + 1 (+1 : count adds the start twice) gives how many objects cannot be compared to the object.
        Use two vectors to record heavier and lighter objects.
        DFS to count all reachable objects from the start.
    Time Complexity:
        O(N+M)
*/