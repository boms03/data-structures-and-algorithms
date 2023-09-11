#include<iostream>
#include<queue>
using namespace std;
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
int hdx[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
int hdy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int map[201][201];
int visited[201][201][31]; 
int w,h,k;

void bfs(){
    queue<pair<pair<int,int>,pair<int,int> > >q;
    q.push({{0,0},{0,0}});
    visited[0][0][0]=1;
    visited[0][0][1]=1;
    while(!q.empty()){
        int x=q.front().first.first;
        int y=q.front().first.second;
        int cnt=q.front().second.first;
        int ability=q.front().second.second;
        q.pop();
        
        if(x==w-1 && y==h-1){
            cout << cnt << '\n';
            return;
        }
        if(ability<k){
            for(int i=0;i<8;i++){
                int nx = x + hdx[i];
                int ny = y + hdy[i];
                if(nx>=0 && ny>=0 && nx<w && ny<h){
                    if(map[ny][nx]==0 && !visited[ny][nx][ability+1]){
                        visited[ny][nx][ability+1]=1;
                        q.push({{nx,ny},{cnt+1,ability+1}});
                    }
                }
            }
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx>=0 && ny>=0 &&nx<w&&ny<h){
                if(map[ny][nx]==0 && !visited[ny][nx][ability]){
                    visited[ny][nx][ability]=1;
                    q.push({{nx,ny},{cnt+1,ability}});
                }
            }
        }
    }
    cout << -1 << '\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> k;
    cin >> w >> h;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            cin>>map[i][j];
        }
    }
    bfs();
}
