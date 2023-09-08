#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
char map[6][6];
int check[26];
int combiSelect[6][6];
int queueSelect[6][6];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
vector<int>combi;
queue<pair<int,int>>q;
int ans;
bool MoreThanFour(){ // [3] check if the combination has equal or more than 4 'S's
    int s = 0;
    for (int i=0; i<7; i++){
        if (map[combi[i]/5][combi[i]%5]=='S') s++;
    }
    if (s>=4){
        return true;
    }
    return false;
}
bool Adjacency(){ // [2] check adjacency by BFS 
    memset(combiSelect, 0, sizeof(combiSelect)); // need to visit
    memset(queueSelect, 0, sizeof(queueSelect)); // visited
    bool checkAnswer = false;
    for (int i=0;i<7;i++){
        int x = combi[i]%5;
        int y = combi[i]/5;
        combiSelect[y][x]=1;
        if (i==0) q.push({x,y});
    }

    int cnt = 0;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (cnt==7){
            checkAnswer = true;
            break;
        }
        for (int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx > 4 || ny < 0 || ny > 4 ) continue;
            if (combiSelect[ny][nx]&& !queueSelect[ny][nx]){
                q.push({nx,ny});
                queueSelect[ny][nx]=1;
                cnt++;
            }
        }
    }
    if (checkAnswer) return true;
    return false;
}
void DFS(int idx, int cnt){
    if(cnt==7){
        if (MoreThanFour()){
            if (Adjacency()){            
                ans++;
            }
        }
        return;
    }
    for(int i=idx;i<25;i++){ // [1] pick 7 combinations
        if(check[i]) continue;
        check[i]=1;
        combi.push_back(i);
        DFS(i+1,cnt+1);
        combi.pop_back();
        check[i]=0;
    }
}

int main(){
    for(int i=0; i<5;i++){
        for(int j=0; j<5;j++){
            scanf(" %c", &map[i][j]);
        }
    }
    DFS(0,0);
    cout << ans << '\n';
}

/*
    [1] 25C7
    [2] O(V+E) too small
    [3] 7 too small
    O(25C7)
*/