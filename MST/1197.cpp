#include <string>
#include <algorithm>
#include <iostream>
#include<vector>
#define pipii pair<int,pair<int,int>>

using namespace std;
int v,e;
int parent[10001];
vector<pipii>info;

void init(){
    for(int i=1;i<=v;i++) parent[i]=i;
}

int find(int a){
    if(parent[a]==a) return a;
    return parent[a] = find(parent[a]);
}

void join(int a, int b){
    int a_root = find(a);
    int b_root = find(b);
    parent[b_root] = a_root;
}

int main() {
    cin >> v >> e;
    init();
    for(int i=0;i<e;i++){
        int a,b,c;
        cin >> a >> b >> c;
        info.push_back({c,{a,b}});
    }
    sort(info.begin(),info.end());
    int ans = 0;
    for(pipii cur: info){
        if(find(cur.second.second)==find(cur.second.first)) continue;
        ans += cur.first;
        join(cur.second.first,cur.second.second);
    }
    cout << ans;
}