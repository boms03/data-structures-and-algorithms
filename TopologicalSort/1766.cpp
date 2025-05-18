// Online C++ compiler to run C++ program online
#include <iostream>
#include <queue>
using namespace std;
int indegree[32001]={0,};
vector<vector<int>>prior;
priority_queue<int, vector<int>, greater<int>> pq;

int n,m;

void tp(){
    while(!pq.empty()){
        int top = pq.top();
        pq.pop();
        cout << top << " ";
        for(int next: prior[top]){
            indegree[next]--;
            if(indegree[next]==0) pq.push(next);
        }
    }
}
int main() {
    cin >> n >> m;
    prior.resize(n+1);
    for(int i=0;i<m;i++){
        int from, to;
        cin >> from >> to;
        prior[from].push_back(to);
        indegree[to]++;
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0) pq.push(i);
    }
    tp();
}