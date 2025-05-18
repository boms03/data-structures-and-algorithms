#include <string>
#include <cstring>
#include <queue>
#include <iostream>
#include<vector>
#define pipii pair<int,pair<int,int>>

using namespace std;
int n,m,rx,ry,d;
int map[51][51];
bool visited[4][51][51];
int dx[4]={0,1,0,-1};
int dy[4]={-1,0,1,0};
int cnt = 0;
void btk(int x, int y, int dir){
    
    //cout << "방향 " << dir << endl;
    //1 청소 가능하면 청소하기
    if(map[y][x]==0){
        map[y][x]=2;
        cnt++;
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<m;j++){
        //         cout << map[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    
    bool cleaned = true;
    //주변 4칸 청소 여부 확인
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx<0 || nx>=m || ny<0 || ny >=n || map[ny][nx]==1) continue;
        if(map[ny][nx]==0){
            //cout << "청소 필요"<<endl;
            cleaned = false;
        }
    }
    
    // 2 모두 청소됨
    if(cleaned){
        //cout << map[y-dy[dir]][x-dx[dir]] << endl;
        if(y-dy[dir]<0 || x-dx[dir] <0 || map[y-dy[dir]][x-dx[dir]]==1){
            cout << cnt;
            exit(0);
        }
        else{
            //cout << "후진"<<endl;
            btk(x-dx[dir],y-dy[dir],dir);
        }
    } else{ // 3 청소 안된 칸 발견
        dir = (dir+3)%4;
        //cout << "3 회전 " << dir <<endl;
        if(y+dy[dir]>=n || x+dx[dir]>=m || map[y+dy[dir]][x+dx[dir]]==0){
            //cout << "3 전방청소 안함 발견 " <<endl;
            btk(x+dx[dir],y+dy[dir],dir);
        } else{
            //cout << "3 회전만함" <<endl;
           btk(x,y,dir);
        }
    }
}

int main() {
    
    cin >> n >> m;
    cin >> ry >> rx >> d;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> map[i][j];
        }
    }
    
    btk(rx,ry,d);
}