
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstring>
#define MAX_NM 9
using namespace std;

int n,m;
int ans = 81;
int map[MAX_NM][MAX_NM];

string p1[]={"0","1","2","3"};
string p2[]={"02","13"};
string p3[]={"01","12","23","03"};
string p4[]={"012","123","023","013"};
string p5[]={"0123"};

vector<pair<int,int>> cctvs;
vector<string> btk_rot;

bool check_bound(int x, int y){
    return (x>=0 && x<m && y>=0 && y<n);
}

void print_right(int x, int y, int (&copy_map)[MAX_NM][MAX_NM]){
    int ny = y;
    int nx = x+1;
    while(check_bound(nx,ny) && copy_map[ny][nx]!=6){
        copy_map[ny][nx]=7;
        nx+=1;
    }
}

void print_left(int x, int y, int (&copy_map)[MAX_NM][MAX_NM]){
    int ny = y;
    int nx = x-1;
    while(check_bound(nx,ny) && copy_map[ny][nx]!=6){
        copy_map[ny][nx]=7;
        nx-=1;
    }
}

void print_up(int x, int y, int (&copy_map)[MAX_NM][MAX_NM]){
    int ny = y-1;
    int nx = x;
    while(check_bound(nx,ny) && copy_map[ny][nx]!=6){
        copy_map[ny][nx]=7;
        ny-=1;
    }
}

void print_down(int x, int y, int (&copy_map)[MAX_NM][MAX_NM]){
    int ny = y+1;
    int nx = x;
    while(check_bound(nx,ny) &&  copy_map[ny][nx]!=6){
        copy_map[ny][nx]=7;
        ny+=1;
    }
}

int print_all(){
    int copy_map[MAX_NM][MAX_NM];
    memcpy(copy_map,map,sizeof(map));

    for (int i=0; i<btk_rot.size(); i++){
        int x = cctvs[i].first;
        int y = cctvs[i].second;
        for(int j=0;j<btk_rot[i].length();j++){
            if(btk_rot[i][j]=='0') print_right(x,y,copy_map);
            else if(btk_rot[i][j]=='1') print_up(x,y,copy_map);
            else if(btk_rot[i][j]=='2') print_left(x,y,copy_map);
            else if(btk_rot[i][j]=='3') print_down(x,y,copy_map);
        }
    }
    int cnt = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(copy_map[i][j]==0) cnt++;
        }
    }
    return cnt;
}
void btk(int idx){
    if(idx==cctvs.size()){
        //for (int i=0; i<btk_rot.size(); i++) cout << btk_rot[i] << " ";
        //cout << '\n';
        ans = min(ans,print_all());
        //cout << ans << endl;
        return;
    }

    if(map[cctvs[idx].second][cctvs[idx].first]==1){
            for(int j=0;j<4;j++){
                btk_rot.push_back(p1[j]);
                //cout << p1[j] << endl;
                btk(idx+1);
                btk_rot.pop_back();
            }
    } else if(map[cctvs[idx].second][cctvs[idx].first]==2){
            for(int j=0;j<2;j++){
                btk_rot.push_back(p2[j]);
                //cout << p2[j] << endl;
                btk(idx+1);
                btk_rot.pop_back();
            }
    } else if(map[cctvs[idx].second][cctvs[idx].first]==3){
            for(int j=0;j<4;j++){
                btk_rot.push_back(p3[j]);
                //cout << p3[j] << endl;
                btk(idx+1);
                btk_rot.pop_back();
            }
    } else if(map[cctvs[idx].second][cctvs[idx].first]==4){
            for(int j=0;j<4;j++){
                btk_rot.push_back(p4[j]);
                //cout << p4[j] << endl;
                btk(idx+1);
                btk_rot.pop_back();
            }
    } else if(map[cctvs[idx].second][cctvs[idx].first]==5){
            btk_rot.push_back(p5[0]);
            //cout << p5[0] << endl;
            btk(idx+1);
            btk_rot.pop_back();
    }
}
int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> map[i][j];
            if(map[i][j]!= 0 && map[i][j]!= 6){
                cctvs.push_back({j,i});
            }
        }

    }
    //cout << cctvs.size() << endl;
    btk(0);
    cout << ans;
}