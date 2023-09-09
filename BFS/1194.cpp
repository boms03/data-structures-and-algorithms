#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int n,m;
char map[51][51];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int visited[51][51][1<<6]; // record visit depending on the current keys 
int startX,startY;

typedef struct{
    int x;
    int y;
    int key; // update when a key found
    int cnt; // keep adding 1
} node;
int bfs(){
    queue<node>q;
    q.push({startX,startY,0,0});
    visited[startY][startX][0]=1;
    while(!q.empty()){
        int x = q.front().x;
        int y = q.front().y;
        int key = q.front().key;
        int cnt = q.front().cnt;
        q.pop();
        if(map[y][x]=='1') return cnt; // the very first 1 found will have the minimum cnt

        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx<0 || ny<0 || nx>=m || ny>=n) continue;
            if(!visited[ny][nx][key]){
                if(map[ny][nx]=='.' || map[ny][nx]=='1' || map[ny][nx]=='0'){ // keep searching if .,1,0
                    visited[ny][nx][key]=1;
                    q.push({nx,ny,key,cnt+1});
                }
                else if('a'<=map[ny][nx]&&map[ny][nx]<='f'){ // when a key found
                    int tmp_key = key | (1 << int(map[ny][nx]-'a')); // or operator adds the found key to the current key (a0b10c100d1000..)
                    visited[ny][nx][tmp_key]=1;
                    q.push({nx,ny,tmp_key,cnt+1});
                }
                else if('A'<=map[ny][nx]&&map[ny][nx]<='F'){ // when a door found
                    if (key & (1<<int(map[ny][nx]-'A'))){ // and operator gives 0 if there is no corresponding 1
                        visited[ny][nx][key]=1;
                        q.push({nx,ny,key,cnt+1});
                    }
                }          
            }
        }
    }
    return -1;
}
int main(){
    cin >> n >> m;
    for (int i=0; i<n; i++){
        string s;
        cin>>s;
        for (int j=0; j<m; j++){
            map[i][j]=s[j];
            if(map[i][j]=='0'){
                startX=j;
                startY=i;
            }

        }
    }

    cout << bfs() << endl;
}