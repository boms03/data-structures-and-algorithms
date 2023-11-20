#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
int n,m;
int map[301][301];
int visited[301][301];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};

void bfs(int j,int i){
    queue<pair<int,int>>q;
    q.push({j,i});
    visited[i][j]=1;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx<0 || ny<0 || nx>=m || ny>=n) continue;
            if(visited[ny][nx]) continue;
            if(map[ny][nx]==0){
                if(map[y][x]!=0) map[y][x]--; // no negative value for map[y][x]
            } else {
                q.push({nx,ny});
                visited[ny][nx]=1;
            }
        }
    }
}
int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0; j<m;j++){
            cin >> map[i][j];
        }
    }

    int year=0;
    while(true){
        int ice = 0;
        for(int i=0;i<n;i++){
            for(int j=0; j<m;j++){
                if(map[i][j]!=0 && !visited[i][j]){
                    bfs(j,i);
                    ice++;
                }
            }
        }
        if(ice>=2){ //ices started to split
            cout << year << '\n';
            exit(0);
        }
        if(ice==0){ // no ices
            cout << 0 << '\n';
            exit(0);
        }
        memset(visited,0,sizeof(visited));
        year++;
    }
    cout << 0 << '\n';

}

/*
    approach: 
    bfs each unvisited ice index to count the number of connected ices
    bfs will happen once if all ices are connected which means the number of bfs is equal to the number of connected ices
    for each ice index, check all directions to see if 1) water or 2)ice
    skip if out of range or already visited
    1) adjacent to water means map[i][j]-- (!) subtract only when map[i][j] is positive
    2) push adjacent ice index and visit

    O(NM)
*/
