#include<iostream>
#include<vector>
using namespace std;

int n,m;
int dist[101][101];
int answer;
int minDist=1e9;

void floyd(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

int main(){

    cin >> n >> m;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            dist[i][j]=1e9;
        }
    }

    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        dist[a-1][b-1]=1;
        dist[b-1][a-1]=1;
    }

    floyd();

    for(int i=0; i<n; i++){
        int total = 0;
        for(int j=0; j<n; j++){
            if(i==j) continue;
            total += dist[i][j];
        }
        if(minDist>total){
            minDist = total;
            answer = i;
        }
    }
    cout << answer+1;


}