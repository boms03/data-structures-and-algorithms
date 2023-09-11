#include<iostream>
#include<cstring>
using namespace std;

int matrix[101][101];
int visited[101];
int ans[101][101];
int n;

void dfs(int start, int now){
    for(int k=0; k<n;k++){
        if (matrix[now][k] && !visited[k]){ // k is the next vertex
            ans[start][k]=1;
            visited[k]=1;
            dfs(start,k);
        }
    }
}
int main(){
    cin >> n;
    for(int i=0; i<n;i++){
        for(int j=0; j<n;j++){
            cin >> matrix[i][j];
        }
    }

    for(int i=0; i<n;i++){ // dfs for each vertex
        dfs(i,i);
        memset(visited,0,sizeof(visited));
    }

    for(int i=0; i<n;i++){
        for(int j=0; j<n;j++){
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}

// DFS O(N^2)