#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int n;
char map[101][101];
int visited[101][101];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};

void bfs(int x, int y, int s){
    queue<pair<int,int>>q;
    q.push({x,y});
    visited[y][x]=1;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        char c = map[y][x];
        q.pop();

        for (int i=0; i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >=n) continue;
            if(!visited[ny][nx]){
                if(s==1){
                    if(map[ny][nx]==c){
                        visited[ny][nx]=1;
                        q.push({nx,ny});
                    }
                } else{
                    if(((c=='R' || c=='G') && (map[ny][nx]=='R' || map[ny][nx]=='G')) || map[ny][nx]==c){ // (1)
                        visited[ny][nx]=1;
                        q.push({nx,ny});
                    }
                }
            } 

        }

    }
}

int main(){
    cin >>n;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<n;j++) map[i][j] = s[j];
    }

    
    int fCnt = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(!visited[i][j]){
                bfs(j,i,1);
                fCnt++;
            }
        }
    }
    memset(visited,0,sizeof(visited));

    int sCnt = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(!visited[i][j]){
                bfs(j,i,2);
                sCnt++;
            }   
        }
    }

    cout << fCnt << " " << sCnt << '\n';
}

/*
    approach: 
        simple BFS problem
        f(1) (c=='R' || c=='G') && (map[ny][nx]=='R' || map[ny][nx]=='G')) 
        ensures that R can bfs to R and G and G can bfs to R and G as well
        don't forget to get || map[ny][nx]==c which is a case for B

        O(N^2)
*/