#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int k=-1;
vector<int>lotto;
int ans[14];
void dfs(int prev, int idx){
    if(idx==6){
        for (int i=0;i<6;i++){
            cout << ans[i] << " ";
        }
        cout << '\n';
        return;
    }
    for(int i=prev;i<lotto.size();i++){
        ans[idx]=lotto[i];
        dfs(i+1,idx+1);
    }
}
int main(){
    while(true){
        cin >> k;
        if (k==0) break;
        for (int i=0; i<k;i++){
            int a;
            cin >> a;
            lotto.push_back(a);
        }
        dfs(0,0);
        cout << '\n';
        lotto.clear();
        memset(ans,0,sizeof(ans));
    }
}

// O(V+E) DFS