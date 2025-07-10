#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <list>
#define pii pair<int,int>
using namespace std;

int map[17][17];
int n, m, d;
int ans = 0;
int enemies = 0;
vector<pii> enemy_points;
vector<int> archer_cols;

void find_ans() {
    list<pii> current_enemies(enemy_points.begin(), enemy_points.end());
    
    int cnt_kill = 0;
    
    while(!current_enemies.empty()) {
        // 각 궁수가 공격할 적 찾기
        vector<list<pii>::iterator> targets;
        
        for(int archer_col : archer_cols) {
            int best_dist = d + 1;
            auto target_it = current_enemies.end();
            
            for(auto it = current_enemies.begin(); it != current_enemies.end(); ++it) {
                int enemy_r = it->first;
                int enemy_c = it->second;
                
                int dist = abs(enemy_r - n) + abs(enemy_c - archer_col);
                if(dist <= d) {
                    if(dist < best_dist || (dist == best_dist && enemy_c < target_it->second)) {
                        best_dist = dist;
                        target_it = it;
                    }
                }
            }
            
            if(target_it != current_enemies.end()) {
                targets.push_back(target_it);
            }
        }
        
        // 중복 제거: 같은 iterator가 있는지 확인하고 제거
        for(int i = 0; i < targets.size(); i++) {
            bool duplicate = false;
            for(int j = 0; j < i; j++) {
                if(targets[i] == targets[j]) {
                    duplicate = true;
                    break;
                }
            }
            if(!duplicate) {
                current_enemies.erase(targets[i]);
                cnt_kill++;
            }
        }
        
        // 적들을 한 칸씩 아래로 이동
        for(auto it = current_enemies.begin(); it != current_enemies.end();) {
            it->first++; // 한 칸 아래로 이동
            if(it->first >= n) { // 성에 도달한 경우
                it = current_enemies.erase(it); // O(1) 삭제하고 다음 iterator 반환
            } else {
                ++it; // 다음 요소로 이동
            }
        }
    }
    
    ans = max(ans, cnt_kill);
}

void backtrack(int cur, int cnt) {
    if(cnt == 3) {
        find_ans();
        return;
    }
    
    if(cur == m) return;
    
    // 현재 위치에 궁수 배치
    archer_cols.push_back(cur);
    backtrack(cur + 1, cnt + 1);
    archer_cols.pop_back();
    
    // 현재 위치에 궁수 배치 안함
    backtrack(cur + 1, cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> d;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> map[i][j];
            if(map[i][j] == 1) {
                enemy_points.push_back({i, j});
                enemies++;
            }
        }
    }
    
    backtrack(0, 0);
    cout << ans << endl;
    
    return 0;
}
