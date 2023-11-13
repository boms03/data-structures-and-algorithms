#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

typedef struct{
    int direction;
    int x;
    int y;
    int cnt;
} info;

int dx[]={1,0,-1,0}; // W S E N
int dy[]={0,1,0,-1};
int dir[]={0,0,2,1,3};


int n,m;
int map[101][101];
int visited[101][101][4];

int bfs(int sx,int sy,int sd,int ex,int ey,int ed){
    queue<info>q;
    q.push({sd,sx,sy,0});
    visited[sy][sx][sd]=1;
    while(!q.empty()){
        int cd = q.front().direction;
        int cx = q.front().x;
        int cy = q.front().y;
        int cnt = q.front().cnt;
        q.pop();

        if(cx==ex && cy==ey && cd ==ed){
            return cnt;
        }

        for(int i=1;i<=3;i++){
            int nx = cx + dx[cd]*i;
            int ny = cy + dy[cd]*i;
            if(map[ny][nx]==1) break;
            if(nx<=0 || nx>m || ny<=0 || ny>n || visited[ny][nx][cd]) continue;
            visited[ny][nx][cd]=1;
            q.push({cd,nx,ny,cnt+1});
        }

        if(!visited[cy][cx][(cd+1)%4]){
            q.push({(cd+1)%4,cx,cy,cnt+1});
            visited[cy][cx][(cd+1)%4]=1;
        }
        if(!visited[cy][cx][(cd+2)%4]){
            q.push({(cd+2)%4,cx,cy,cnt+2});
            visited[cy][cx][(cd+2)%4]=1;
        }

        if(!visited[cy][cx][(cd+3)%4]){
            q.push({(cd+3)%4,cx,cy,cnt+1});
            visited[cy][cx][(cd+3)%4]=1;
        }

    }
    return -1;
}

int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> map[i][j];
        }
    }
    int sy,sx,sd,ey,ex,ed;
    cin >> sy >> sx >> sd;
    cin >> ey >> ex >> ed;

    cout << bfs(sx,sy,dir[sd],ex,ey,dir[ed]) << '\n';

}

/*
    Approach:
        The key point is to convert 1(west), 2(east), 3(south), 4(north) to 0(west),1(south),2(east),3(north).
        It eases the computation when turning direction,
        During BFS, we have two major functions.
        The first function is to move:
            We can move 1,2,3 steps but the path should be all 0s.
        The second function is to turn:
            South<->North and West<->East takes 2 steps.
        (!) visited array should be 3 dimentional because it depends on the directions.
*/