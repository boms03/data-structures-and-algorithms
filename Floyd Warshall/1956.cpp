#include<iostream>
using namespace std;

int v,e;
int dist[401][401];
int answer;
int minDist=1e9;

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
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b]= c;
    }

    floyd();

    int answer = 1e9;
    for(int i=1;i<=v;i++){
        for(int j=1;j<=v;j++){
            if(i==j) continue;
            answer = min(answer,dist[i][j]+dist[j][i]);
        }
    }
    if(answer==1e9) cout << -1;
    else cout << answer;
}

/*
    Approach:
        Use floyd warshall as it requires all pair distances.
        Calculate the minimum round trip distance using the minimum distance info
        ex) Minimum of every two pair (a to b) + (b to a)
            (!) If the minimum distance is inf, it means no available round trip (-1)
    Time Complexity:
        O(N^3)
*/