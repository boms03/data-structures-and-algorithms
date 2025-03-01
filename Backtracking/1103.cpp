#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int map[51][51];
bool visited[51][51];
int dp[51][51];  
int n, m;
int ans = 0;

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

int btk(int x, int y) {
    if (dp[y][x] != -1) return dp[y][x];

    visited[y][x] = true; 
    dp[y][x] = 1; 

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i] * map[y][x];
        int ny = y + dy[i] * map[y][x];

        if (nx < 0 || nx >= m || ny < 0 || ny >= n || map[ny][nx] == -1) {
            continue;
        }

        if (visited[ny][nx]) {
            cout << -1;
            exit(0);
        }

        dp[y][x] = max(dp[y][x], btk(nx, ny) + 1);
    }

    visited[y][x] = false;
    return dp[y][x];
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == 'H') {
                map[i][j] = -1;  
            } else {
                map[i][j] = s[j] - '0';
            }
        }
    }

    memset(dp, -1, sizeof(dp));

    cout << btk(0, 0);
}
