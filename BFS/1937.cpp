#include<iostream>
#include<algorithm>
#define MAX_N 501
using namespace std;
int n;
int map[MAX_N][MAX_N];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
int dp[MAX_N][MAX_N];

int dfs(int y, int x){
    if(dp[y][x]) return dp[y][x];
    dp[y][x] = 1;
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(ny<0 || ny >=n || nx < 0 || nx >= n)continue;
        if(map[ny][nx] > map[y][x]){
            dp[y][x] = max(dp[y][x], dfs(ny, nx) + 1);
        }
    }
    return dp[y][x];

}

int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0; j<n;j++){
            cin >> map[i][j];
        }
    }

    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=0; j<n;j++){
            ans = max(ans , dfs(i,j));
        }
    }
    cout << ans;
}