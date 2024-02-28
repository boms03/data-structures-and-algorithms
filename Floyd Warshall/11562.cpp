#include<iostream>
using namespace std;

int v,e,t;
int dist[251][251];

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

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> v >> e;

    for(int i=1; i<=v; i++){
        for(int j=1; j<=v; j++){
            if(i!=j) dist[i][j]=1e9;
        }
    }
    
    int a, b, c;
    for(int i=0; i<e; i++){
        cin >> a >> b >> c;
        dist[a][b]=0;
        c==1 ? dist[b][a] = 0 : dist[b][a] = 1;
    }

    floyd();

    cin >> t;

    while(t--){
        cin >> a >> b;
        cout << dist[a][b] << '\n';
    }
}

/*
    Approach:
        Use floyd warshall as it requires all pair costs.
        Cost is 1 when moving backward from node A to node B.
        Cost is 0 when moving forward.
        The minimum cost from A to B equals to the minumum number of backward movements needed.
        Therefore, the cost is the number of one way roads that should be fixed to bidirectional roads.
    Time Complexity:
        O(V^3);
*/
