#include<iostream>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int,pair<int,int>> piii;

vector<pair<int,int>>water;
int map[51][51];
bool visited[51][51];
int dx,dy;
int sx,sy;
int n,m;

int move_x[4] = {0,0,-1,1}; 
int move_y[4] = {1,-1,0,0};

void water_bfs(){
    queue<piii> q;
    for(int i=0;i<water.size();i++){
        q.push({0,{water[i].first,water[i].second}});
        visited[water[i].second][water[i].first] = true;
    }
    while(!q.empty()){
        piii cur = q.front();
        q.pop();

        int cur_time = cur.first;
        int cur_x = cur.second.first;
        int cur_y = cur.second.second;

        map[cur_y][cur_x] = cur_time;

        for(int i=0;i<4;i++){
            int next_x = cur_x + move_x[i];
            int next_y = cur_y + move_y[i];

            if(next_x<0 || next_x>=m || next_y<0 || next_y >=n || map[next_y][next_x] == -4 || map[next_y][next_x] == -2 || map[next_y][next_x] == -1 || visited[next_y][next_x]) continue;
            q.push({cur_time+1,{next_x,next_y}});
            visited[next_y][next_x] = true;
        }
    }
}

int move_bfs(){
    queue<piii> q;
    q.push({0,{sx,sy}});
    visited[sy][sx] = true;
    while(!q.empty()){
        piii cur = q.front();
        q.pop();

        int cur_time = cur.first;
        int cur_x = cur.second.first;
        int cur_y = cur.second.second;

        map[cur_y][cur_x] = cur_time;

        if(cur_x == dx && cur_y == dy) return cur_time;

        for(int i=0;i<4;i++){
            int next_x = cur_x + move_x[i];
            int next_y = cur_y + move_y[i];
            if(next_x<0 || next_x>=m || next_y <0 || next_y >=n || map[next_y][next_x] == -4 || visited[next_y][next_x]) continue;
            if(map[next_y][next_x]==-2 || map[next_y][next_x]==0 || map[next_y][next_x] > cur_time+1 ){
                q.push({cur_time+1,{next_x,next_y}});
                visited[next_y][next_x] = true;
            }
        }
    }
    return -1;
}

int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char input;
            cin >> input;
            if (input == 'S') {
                map[i][j] = -1;
                sx = j;
                sy = i;
            } else if (input == 'D') {
                map[i][j] = -2;
                dx = j;
                dy = i;
            } else if (input == '*') {
                map[i][j] = -3;
                water.push_back({j,i});
            } else if (input == 'X') {
                map[i][j] = -4;
            }
        }
    }
    water_bfs();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << map[i][j] << " " ;
        }
        cout << endl;
    }
    fill(&visited[0][0], &visited[0][0] + 51*51, false);
    int result = move_bfs();
    if(result==-1) cout << "KAKTUS";
    else cout << result;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << map[i][j] << " " ;
        }
        cout << endl;
    }

}