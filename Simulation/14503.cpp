#include<iostream>
using namespace std;


int n,m;
bool done = false;
int y,x,d;
int map[51][51];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
// 0북 1동 2남 3서

void rotate(int current_direction){
    if(current_direction==0){
        d = 3;
    } else {
        d--;
    }
}

void move(int current_direction, int move_direction){
    if(current_direction==0){
        if(move_direction==1){
            if(y-1<0||map[y-1][x]==1||map[y-1][x]==3) return;
            y-=1;
        } else{
            if(y+1>=n||map[y+1][x]==1) done = true;
            y+=1;
        }
    }
    else if(current_direction==1){
        if(move_direction==1){
            if(x+1>=m||map[y][x+1]==1||map[y][x+1]==3) return;
            x+=1;
        } else{
            if(x-1<0||map[y][x-1]==1) done = true;
            x-=1;
        }
    }
    else if(current_direction==2){
        if(move_direction==1){
            if(y+1>=n||map[y+1][x]==1||map[y+1][x]==3) return;
            y+=1;
        } else{
            if(y-1<0||map[y-1][x]==1) done = true;
            y-=1;
        }
    }
    else if(current_direction==3){
        if(move_direction==1){
            if(x-1<0||map[y][x-1]==1||map[y][x-1]==3) return;
            x-=1;
        } else{
            if(x+1>=m||map[y][x+1]==1) done = true;
            x+=1;
        }
    }
}

int ans = 0;

int main(){
    cin >> n >> m;
    cin >> y >> x >> d;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> map[i][j];
        }
    }

    while(!done){

        if(map[y][x]==0){
            map[y][x]=3;
            ans++;
        }

        bool nCleaned = true;

        for(int i=0;i<4;i++){

            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx<0 || nx >=m || ny<0 || ny >=n) continue;

            if(map[ny][nx]==0){
                nCleaned = false;
                rotate(d);
                move(d,1);
                break;
            }
        }

        if(nCleaned){
            move(d,0);
        }
    }
    cout << ans << '\n';
}