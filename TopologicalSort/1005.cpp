#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#define pii pair<int,int>
using namespace std;

vector<vector<int>>prebuild;
int take[1001];
int income[1001];
int ans[1001];
int t, n, k, w;

void topological_sort(queue<pii>&zeros){
    while(!zeros.empty()){
        pii out = zeros.front();
        zeros.pop();
        if(out.first == w) break;
        for(int i=0;i<int(prebuild[out.first].size());i++){
            int next = prebuild[out.first][i];
            ans[next]=max(ans[next], out.second+take[next]);
            if(--income[next] == 0) zeros.push({next,ans[next]});
        }
    }
}
int main(){
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> t;
    while(t--){
        cin >> n >> k;
        prebuild.clear();
        prebuild.resize(n+1);
        memset(ans, 0, sizeof(ans));
        memset(income, 0, sizeof(income));
        for(int i=1;i<=n;i++){
            cin >> take[i];
        }
        for(int i=1;i<=k;i++){
            int x, y;
            cin >> x >> y;
            prebuild[x].push_back(y);
            income[y]++;
        }
        queue<pii>zeros;
        for(int i=1;i<=n;i++){
            if(income[i]==0){
                zeros.push({i,take[i]});
                ans[i]=take[i];
            }
        }
        cin >> w;
        topological_sort(zeros);
        cout << ans[w] << '\n';
    }
}

/*
    O(T(N+K))
*/