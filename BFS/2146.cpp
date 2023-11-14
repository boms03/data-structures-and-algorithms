#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n;
int map[101][101];
int visited[101][101];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

void labelBFS(int sx, int sy, int group){
    queue<pair<int,int>>q;
    q.push({sx,sy});
    map[sy][sx]=group;
    while(!q.empty()){
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for(int i=0;i<4;i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx < 0 || nx >= n || ny < 0 || ny >=n) continue;
            
            if(map[ny][nx]==1 && !visited[ny][nx]){
                map[ny][nx]=group;
                visited[ny][nx]=1;
                q.push({nx,ny});
            }
        }
    }
}

int bridgeBFS(int cx, int cy){
    queue<pair<int,int>>q;
    int g = map[cy][cx];
    q.push({cx,cy});
    while(!q.empty()){
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        if(map[cy][cx]!=0 && map[cy][cx]!=g){
            return visited[cy][cx];
        }

        for(int i=0;i<4;i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx < 0 || nx >= n || ny < 0 || ny >=n) continue;
            
            if(map[ny][nx]!=g && !visited[ny][nx]){
                visited[ny][nx]=visited[cy][cx]+1;
                q.push({nx,ny});
            }
        }
    }
    return 1e9;
}

int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>map[i][j];
        }
    }
    int group = 2;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(map[i][j]==1){
                labelBFS(j,i,group);
                group++;
            }
        }
    }

    memset(visited,0,sizeof(visited));
    int mn = 1e9;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(map[i][j]!=0){
                mn = min(mn,bridgeBFS(j,i)-1);
                memset(visited,0,sizeof(visited));
            }
        }
    }
    cout << mn << endl;
}

/*
    Approach:
        Use DFS or BFS to label each island.
        labelBFS maps all adjacent 1s to group number>=2.
        After the labeling, use bridgeBFS to find the shortest path from one island to any other islands.
        Cannot use DFS during the bridge making process, because it does not guarantee the shortest path.

    Time Complexity:
        One BFS: O(V+4V)= O(5V) = O(5N^2)
        Perform BFS for each index = O(5N^4) = O(N^4)
        But non edge indexs perform O(1)     

        O(N^4) , N<=100


*/
