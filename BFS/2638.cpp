#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int n,m,last,result,lastTime;
int map[101][101];
int visited[101][101];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

int bfs(){
    queue<pair<int,int>>q;
    q.push({0,0});
    visited[0][0]=1;
    bool cheese = false;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx<0 || nx>=m || ny<0 || ny>=n) continue;

            if(map[ny][nx]==0 && visited[ny][nx]==0){ // not cheese
                q.push({nx,ny});
                visited[ny][nx]=1;
            }
            if(map[ny][nx]!=0){ // cheese contacted
                visited[ny][nx]++;
                cheese=true; // cheese exisit  
            }

            if(visited[ny][nx]==2) map[ny][nx]=0; // delete if contacted twice
        }
    }
    if(!cheese) return 0; // no cheese left
    return 1;
}

int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> map[i][j];
        }
    }
    int t=0;
    while(true){
        if(bfs()) t++;
        else break;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout << map[i][j] << ' ';
            }
            cout << endl;
        }

        memset(visited,0,sizeof(visited));
    }
    cout << t << '\n';
}


/*
    Approach: 
        Start BFS from {0,0} and count how many time a cheese index got contacted.
        If it got contacted twice, it is deleted and becomes 0.
        Keep repeating until the cheese is gone.
*/