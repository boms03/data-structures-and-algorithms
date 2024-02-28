#include<iostream>
using namespace std;

int v,e;
int dist[501][501];

void floyd(){
    for(int k=1;k<=v;k++){
        for(int i=1;i<=v;i++){
            for(int j=1;j<=v;j++){
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

int main(){

    cin >> v >> e;

    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(i!=j) dist[i][j]=1e9;
        }
    }
    
    for(int i=0; i<e; i++){
        int a, b;
        cin >> a >> b;
        dist[a][b]=1;
    }

    floyd();

    int ans = 0;
    int cnt = 1;
    bool check = false;

    for(int i=1;i<=v;i++){
        for(int j=1;j<=v;j++){
            if(i==j) continue;
            if(dist[i][j]!=1e9) cnt++;
        }
        for(int j=1;j<=v;j++){
            if(i==j) continue;
            if(dist[j][i]!=1e9) cnt++;
        }
        if(cnt==v) ans++;
        cnt = 1;
    }
    cout << ans;
}

/*
    Approach:
        Use floyd warshall to check reachability of all pairs
        1] Count the number of nodes reachabe to a node.
        2] Then the number of nodes reachabe from the node.
        The node is rankable if sum of 1 and 2 equals to the total number of nodes.
    Time Complexity:
        O(V^3)
*/
