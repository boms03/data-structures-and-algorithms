#include<iostream>
#include<stack>
#include<vector>
using namespace std;
int n,m,k;
vector<int>v[101];
int visited[101][101];
int map[101][101];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};

int mcnt=0;
int cnt=0;
stack<pair<int,int>>s;


// void dfs(int y, int x){
//     for(int i=0;i<4;i++){
//         int nx = x + dx[i];
//         int ny = y + dy[i];
//         if(nx<=0 || nx > m || ny <=0 || ny > n || visited[ny][nx]) continue;

//         if(map[ny][nx]==1){
//             visited[ny][nx]=1;
//             cnt++;
//             dfs(ny,nx);
//         }
//     }
// }

void dfs(int y, int x){
    cnt = 1;
    s.push({y,x});
    while(!s.empty()){
        int cy = s.top().first;
        int cx = s.top().second;
        s.pop();
        for(int i=0;i<4;i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            
            
            if(nx<=0 || nx > m || ny <=0 || ny > n) continue;

            if(map[ny][nx]==1 && !visited[ny][nx]){

                visited[ny][nx]=1;
                cnt++;
                s.push({ny,nx});
            }
        }   
    }
}
int main(){
    cin >> n >> m >> k;
    for (int i=0; i<k; i++){
        int a,b;
        cin >> a >> b;
        map[a][b]=1;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(map[i][j]==1 && !visited[i][j]){
                visited[i][j]=1;
                dfs(i,j);
                mcnt=max(mcnt,cnt);
                cnt=0;
            }
        }
    }
    cout << mcnt << endl;
}


/*
    Approach:
        Use DFS to count all adjacent 1s of each group and find the maximum.
        1s indexs are visited only once.
        Incrememnt cnt everytime unvisited 1s are pushed into the stack.
        When DFS is done, update maximum cnt and repeat DFS for unvisited 1s which belong to different groups.
    Time Compleixty:
        O(NM)
*/

