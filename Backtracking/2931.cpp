#include<iostream>
using namespace std;

// 동 서 남 북
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
char options[7] = {'|','-','+','1','2','3','4'};

char map[26][26];
int n,m;
int mx,my,zx,zy;
char ans;
int ax,ay;

int get_dir(int dir, char hose){
    int ndir = -1;
    if( hose=='|' ){
        // 북 남 방향 그대로
        if(dir == 2 || dir == 3) return dir;
    } else if(hose=='-'){
        // 동 서 방향 그대로
        if(dir == 0 || dir == 1) return dir;
    } else if(hose=='+'){
        // 동서남북 방향 그대로
        if(dir == 0 || dir == 1 || dir == 2 || dir == 3) return dir;
    } else if(hose=='1'){
        // 서 -> 남
        if(dir == 1) return 2;
        // 북 -> 동
        else if(dir == 3) return 0;
    } else if(hose=='2'){
        // 남 -> 동
        if(dir == 2) return 0;
        // 서 -> 북
        else if(dir == 1) return 3;
    } else if(hose=='3'){
        // 동 -> 북
        if(dir == 0) return 3;
        // 남 -> 서
        else if(dir == 2) return 1;
    } else if(hose=='4') {
        // 동 -> 남
        if(dir == 0) return 2;
        // 북 -> 서
        else if(dir == 3) return 1;
    } else {
        return -2;
    }
    return ndir;
}

void btk(int dir, int x, int y, bool retry){
    int ndir = get_dir(dir, map[y][x]);
    if(map[y][x]=='Z'){
        // cout << "found" << endl;
        cout << ay+1 << " " << ax+1 << " " << ans << endl;
        exit(0);
    }
    if(ndir==-1){
        // cout << "back" << endl;
        return;
    }
    else if(ndir==-2 && !retry){
        // cout << "blank found" << endl;
        // cout << y << " " << x << endl;
        ax = x;
        ay = y;
        
        for(char option: options){
            map[y][x] = option;
            ans = map[y][x];
            int nndir = get_dir(dir,map[y][x]);
            if(nndir!=-1 && nndir!=-2){
                // cout << "try " << option << endl;
                int nx = x+dx[nndir];
                int ny = y+dy[nndir];
                if(nx<0 || nx >m || ny < 0 || ny >n){
                    // cout << "out of bound" << endl;
                    continue;
                }
                btk(nndir,x+dx[nndir], y+dy[nndir], true);
                // cout << "failed " << option << endl;
            } else {
                // cout << "not trying " << option << endl;
            }
        }
        return;
    }else if(ndir==-2){
        return;
    }
    //cout << x << " " << y << endl;
    btk(ndir,x+dx[ndir], y+dy[ndir],retry);
}

int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> map[i][j];
            if(map[i][j]=='M'){
                mx=j;
                my=i;
            }
        }
    }
    for(int i=0;i<4;i++){
        int nx = mx + dx[i];
        int ny = my + dy[i];
        if(ny<0 || ny >n || nx < 0 || nx > m) continue;
        //cout << map[ny][nx] << endl;
        if(map[ny][nx]!='.'){
            //cout << "start" << endl;
            btk(i,nx,ny,false);
        }
    }
}