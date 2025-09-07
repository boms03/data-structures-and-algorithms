#include<iostream>
#define MAX_NM 21
using namespace std;

int dice[6];
int map[MAX_NM][MAX_NM];
int n, m, k, x, y;

void move(int op) {
    if(op == 1) { 
        if(y + 1 >= m) return;
        y++;
        int temp = dice[2];
        dice[2] = dice[3];
        dice[3] = dice[5];
        dice[5] = dice[1];
        dice[1] = temp;
    } else if(op == 2) {
        if(y - 1 < 0) return;
        y--;
        int temp = dice[2];
        dice[2] = dice[1];
        dice[1] = dice[5];
        dice[5] = dice[3];
        dice[3] = temp;
    } else if(op == 3) {
        if(x - 1 < 0) return;
        x--;
        int temp = dice[5];
        dice[5] = dice[4];
        dice[4] = dice[2];
        dice[2] = dice[0];
        dice[0] = temp;
    } else if(op == 4) { 
        if(x + 1 >= n) return;
        x++;
        int temp = dice[0];
        dice[0] = dice[2];
        dice[2] = dice[4];
        dice[4] = dice[5];
        dice[5] = temp;
    }

    if(map[x][y] == 0) {
        map[x][y] = dice[2];
    } else {
        dice[2] = map[x][y];
        map[x][y] = 0;
    }
    cout << dice[5] << '\n';
}

int main() {
    cin >> n >> m >> x >> y >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }
    while(k--) {
        int op;
        cin >> op;
        move(op);
    }
    return 0;
}