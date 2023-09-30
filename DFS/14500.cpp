#include<iostream>
using namespace std;

int n,m;
int map[505][505];
int dx[]={0,0,1,-1};
int dy[]={-1,1,0,0};
bool visited[505][505];
int ans = 0;


void dfs(int y, int x, int sum,int depth){
    if(depth==4){
        ans = max(ans,sum);
        return;
    }

    // depth 1: 1 depth 2: 2 depth 3: 3 depth 4: 4

    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx<0 || nx>=m || ny<0 || ny>=n) continue;
        if(!visited[ny][nx]){
            if(depth==2){
                visited[ny][nx]=true;
                dfs(y,x, sum+map[ny][nx], depth+1);
                visited[ny][nx]=false;
            } 
            visited[ny][nx]=true;
            dfs(ny,nx, sum+map[ny][nx], depth+1);
            visited[ny][nx]=false;
        }
    }
}


// void special(int y, int x){
//     //ㅜ
//     if(x>=0 &&  x+2 < m && y>=0 && y+1<n){
//         int sum = map[y][x]+map[y][x+1]+map[y][x+2]+map[y+1][x+1];
//         ans = max(ans,sum);
//     }

//     //ㅏ
//     if(x>=0 &&  x+1 <m && y>=0 && y+2<n){
//         int sum = map[y][x]+map[y+1][x]+map[y+2][x]+map[y+1][x+1];
//         ans = max(ans,sum);
//     }
//     //ㅗ
//     if(x>=0 &&  x+2 <m && y-1>=0 && y<n){
//         int sum = map[y][x]+map[y][x+1]+map[y-1][x+1]+map[y][x+2];
//         ans = max(ans,sum);
//     }

//     //ㅓ
//     if(x>=0 &&  x+1 <m && y-1>=0 && y+1<n){
//         int sum = map[y][x]+map[y][x+1]+map[y-1][x+1]+map[y+1][x+1];
//         ans = max(ans,sum);
//     }
// }


int main(){
    cin>> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0; j<m;j++){
            cin >> map[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0; j<m;j++){
            visited[i][j]=true;
            dfs(i,j,map[i][j],1);
            visited[i][j]=false;
            // special(i,j);
        }
    }
    cout << ans << '\n';
}

/*
    Approach:
        ----, --, |  , |    
            , --, |  , | _
            ,   , | _,    |
        Rotating and fliping these shapes are the same as the DFS path with depth 4.
        The shapes can be traced by using backtracking during DFS.
        ---
         |
        But rotating and fliping this shape is same as the DFS path with depth 3.
        The shapes can be traced by calling DFS from x,y again instead of nx, ny when depth is 2 and visiting nx,ny.
        - (x,y) (nx,ny)
            |
*/