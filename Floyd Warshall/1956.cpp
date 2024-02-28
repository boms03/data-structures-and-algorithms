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
        Use floyd warshall to record context of every two incidents.
        The distance between two incidents equals the number of incidents between + two incidents.
        But we only need to know which incident (A or B) happened beforehand
        1] if dist[A][B] is not inf -> A happened before B
        2] if dist[B][A] is not inf -> B happened before A
        3] if both dist[A][B] and dist[B][A] are inf -> we do not know
    Time Complexity:
        O(N^3)
*/