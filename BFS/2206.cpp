#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef struct {
    int x;
    int y;
    int wall;
}st;


int N,M;
int map[1002][1002];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
int visited[1002][1002][2];

void bfs(){
    queue<st>q;
    q.push({1,1,0});
    visited[1][1][0] = visited[1][1][1] = 1; // don't come back to the initial point

    if(N==1 && M==1){ // end if the final point is the initial point
        cout << 1 << '\n';
        return;
    }

    while(!q.empty()){
        int x = q.front().x;
        int y = q.front().y;
        int wall = q.front().wall;
        q.pop();

        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx>=1 && nx<=M && ny>=1 && ny <=N){
                // if the next point is a wall, haven't broken a wall, and not visited
                if (map[ny][nx]==1 && wall==0 && visited[ny][nx][wall+1]==0){
                    visited[ny][nx][wall+1]=visited[y][x][wall]+1;
                    q.push({nx,ny,wall+1});
                } 
                // if the next point is not a wall and not visited
                if (map[ny][nx]==0 && visited[ny][nx][wall]==0){
                    visited[ny][nx][wall]=visited[y][x][wall]+1;
                    q.push({nx,ny,wall});
                }
                // reached the final point
                if (nx==M && ny==N){
                    if(wall==0){
                        cout << visited[ny][nx][0] << '\n';
                    } else {
                        cout << visited[ny][nx][1] << '\n';
                    }
                    return;
                }
            }
            
        }
    }
    // didn't reach the final point
    cout << -1 << '\n';
}
int main(){
    cin >> N >> M;
    for (int i=1; i<=N;i++){
        for (int j=1; j<=M; j++){
            scanf("%1d", &map[i][j]);
        }
    }
    bfs();
}

/*
    Approach:
        Addition of breaking the wall option to the basic BFS method.
        There are two possible options when vising the next index.
        1) If a wall, not broken a wall yet, and not visited
        2) Not a wall and not visited
        Update visited array of next index by adding 1 to that of current index.
        Keep pushing by level into the queue and pop until the next index is the final point.

    Time Complexity:
        BFS O((N*M)^2) == O(V^2)

*/