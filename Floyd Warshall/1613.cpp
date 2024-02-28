#include<iostream>
#include<vector>
using namespace std;

int n,k,s;
int dist[401][401];
int answer;
int minDist=1e9;

void floyd(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            dist[i][j]=1e9;
        }
    }
    
    for(int i=0; i<k; i++){
        int a, b;
        cin >> a >> b;
        dist[a][b]=1;
    }

    floyd();

    cin >> s;

    for(int i=0; i<s; i++){
        int a,b;
        cin >> a >> b;

        if(dist[a][b]== 1e9 && dist[b][a]== 1e9){
            cout << 0 << '\n';
        }

        if(dist[a][b]!= 1e9){
            cout << -1 << '\n';
        }

        if(dist[b][a]!= 1e9){
            cout << 1 << '\n';
        }
    }

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