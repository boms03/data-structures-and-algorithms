#include<iostream>
#include<queue>
#define pii pair<int,int>
using namespace std;

int n,m;
int ladder[101] = {0,}; 
int snake[101] = {0,};
bool visited[101];

int bfs(){
    queue<pii>q;
    q.push({1,0});
    visited[1]=true;
    while(!q.empty()){
        pii cur = q.front();
        q.pop();
        if (cur.first == 100) return cur.second;
        for(int next=cur.first+1;next<=cur.first+6 && next<=100;next++){
            if (visited[next]) continue;
            if(ladder[next]!=0){
                q.push({ladder[next],cur.second+1});
                visited[ladder[next]] = true;
            }
            else if(snake[next]!=0){
                q.push({snake[next],cur.second+1});
                visited[snake[next]] = true;
            }
            else q.push({next,cur.second+1});
            visited[next]=true;
        }
    }
}

int main(){
    cin >> n >> m;
    int from,to;
    for(int i=0;i<n;i++){
        cin >> from >> to;
        ladder[from] = to;
    }
    for(int i=0;i<m;i++){
        cin >> from >> to;
        snake[from] = to;
    }
    cout << bfs();
}

/*
    O(N+M)
*/