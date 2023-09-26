#include<iostream>
#include<queue>
using namespace std;
int minD, minX, minY, sx, sy, n, eat,ans;
int sharkSize = 2;
int map[21][21];
int visited[21][21];
int dx[]={0,-1,1,0};
int dy[]={1,0,0,-1};

void init(){
    memset(visited,-1,sizeof(visited));
    minD= 1e9;
    minX= 1e9;
    minY= 1e9;
}
void bfs(){
    queue<pair<int,int>>q;
    q.push({sx,sy});
    visited[sy][sx]=0;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx<0 || nx >=n || ny <0 || ny >= n) continue;
            if(visited[ny][nx]!=-1 || map[ny][nx]> sharkSize) continue;

            visited[ny][nx]=visited[y][x]+1;

            if(map[ny][nx]!=0 && map[ny][nx]<sharkSize){
                if(visited[ny][nx]<minD){
                    minD=visited[ny][nx];
                    minX=nx;
                    minY=ny;
                } else if(visited[ny][nx]==minD){
                    if(minY==ny){
                        if(minX>nx){
                            minX = nx;
                            minY = ny;
                        }
                    } else if(minY>ny){
                        minX = nx;
                        minY = ny;
                    }
                }
            }
            q.push({nx,ny});
        }
    }
}
int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> map[i][j];

            if(map[i][j]==9){
                sy = i;
                sx = j;
                map[i][j]=0;
            }
        }
    }
    while(true){
        init();
        bfs();
        if(minX!=1e9 && minY!=1e9){
            ans+=visited[minY][minX];
            eat++;
            if(eat==sharkSize){
                sharkSize++;
                eat=0;
            }
            map[minY][minX]=0;
            sx = minX;
            sy = minY;
        } else{
            break;
        }
    }
    cout << ans;
}

/*
    Approach:
        The shark eats a fish and gets bigger when it eats its current size number of fishes.
        Every time the shark chooses to eat a fish, it eats the one closest to it.
        This means that fish travel by BFS to find the closest edible fish.
        After eating a fish, it BFS again from that index to find the next edible fish.
        If there are fishes that are placed at the same distance, one that is placed more upward and leftward gets eaten.

        BFS
        1. just pass: same size or 0
        2. eat: fish size < shark size
            1. check if the distance of fish is minimum.
                1. update index and distance if the new distance is minimum
                2. check upward and leftward if the new distance is equal to the current minimum distance

        While Loop
        1. keep BFS if the shark ate a fish
            1. if not return the time took to ate the last fish
        2. increase shark size if it ate 2 fishes
        3. make the value of index of eaten fish to 0 so that it can pass there freely in the next BFS
        
*/