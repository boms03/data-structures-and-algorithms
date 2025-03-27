#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int N, M;
char board[11][11];
int dx[4] = { 0, 0, 1, -1 }; // 오른쪽, 왼쪽, 아래, 위
int dy[4] = { 1, -1, 0, 0 };
bool visited[11][11][11][11]; // (빨간 구슬 위치, 파란 구슬 위치) 방문 처리

// 구슬이 이동하는 함수
void moveBall(int& x, int& y, int dx, int dy) {
    while (board[y + dy][x + dx] != '#' && board[y][x] != 'O') {
        x += dx;
        y += dy;
    }
}

int bfs() {
    queue<tuple<int, int, int, int, int>> q; // (빨간 구슬 x, 빨간 구슬 y, 파란 구슬 x, 파란 구슬 y, 현재 횟수)
    int rx, ry, bx, by;
    
    // 입력 받은 보드에서 빨간 구슬과 파란 구슬의 위치를 찾기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] == 'R') {
                rx = j; ry = i;
            }
            if (board[i][j] == 'B') {
                bx = j; by = i;
            }
        }
    }
    
    q.push({rx, ry, bx, by, 0});
    visited[ry][rx][by][bx] = true;
    
    while (!q.empty()) {
        auto [rx, ry, bx, by, cnt] = q.front();
        q.pop();
        
        if (cnt >= 10) continue;
        
        // 네 방향에 대해 구슬을 이동
        for (int i = 0; i < 4; i++) {
            int n_rx = rx, n_ry = ry, n_bx = bx, n_by = by;
            
            // 빨간 구슬과 파란 구슬을 각각 이동
            moveBall(n_rx, n_ry, dx[i], dy[i]);
            moveBall(n_bx, n_by, dx[i], dy[i]);
            
            // 파란 구슬이 구멍에 빠지면 실패
            if (board[n_by][n_bx] == 'O') continue;
            
            // 빨간 구슬이 구멍에 빠지면 성공
            if (board[n_ry][n_rx] == 'O') {
                return cnt + 1;
            }
            
            if (n_rx == n_bx && n_ry == n_by) {
                // 구슬이 겹쳤을 때, 더 멀리 간 구슬을 되돌리기
                if (abs(n_rx - rx) + abs(n_ry - ry) > abs(n_bx - bx) + abs(n_by - by)) {
                    n_rx -= dx[i];
                    n_ry -= dy[i];
                } else {
                    n_bx -= dx[i];
                    n_by -= dy[i];
                }
            }

            // 방문하지 않은 상태라면 큐에 넣기
            if (!visited[n_ry][n_rx][n_by][n_bx]) {
                visited[n_ry][n_rx][n_by][n_bx] = true;
                q.push({n_rx, n_ry, n_bx, n_by, cnt + 1});
            }
        }
    }
    
    return -1;
}

int main() {
    cin >> N >> M;
    
    for (int i = 0; i < N; i++) {
        cin >> board[i];
    }
    
    cout << bfs() << endl;
    
    return 0;
}

/*
    O(N*M)
*/