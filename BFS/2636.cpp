#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,last,result,lastTime;
int map[101][101];
int visited[101][101];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
typedef struct{
    int x;
    int y;
} cheese;

bool BFS(){
    int cnt=0;
    queue<cheese>q;
    q.push({0,0}); // search from 0,0
    while(!q.empty()){
        int x = q.front().x;
        int y = q.front().y;
        q.pop();
        for (int i=0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx<0||nx>=m||ny<0||ny>=n) continue;
            if(!visited[ny][nx]){
                visited[ny][nx]=1;
                if (map[ny][nx]==0){ // continue searching if 0
                    q.push({nx,ny});

                } else { // no further search if cheese 1 is found and count cheeses 
                    map[ny][nx]=0;
                    cnt++;
                }
            }
        }
    }
    if(cnt){
        result=cnt;
        return true;
    }
    return false;

}
int main(){
    cin >> n >> m;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> map[i][j];
        }
    }
    while(true){
        if(!BFS()) break;
        lastTime++; 
        memset(visited,0,sizeof(visited));
    }

    cout << lastTime << endl;
    cout << result << endl;
}

/*
    V=n*m
    O(lastTime*V^2)

    n<=100 m<=100 lastTime<=50
    50*100,000 < 1e8
*/