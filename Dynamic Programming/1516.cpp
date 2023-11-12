#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef struct {
    int time;
    vector<int>before;
} info;

info arr[501];
int dp[501];
int n;

int solve(int num){
    if(dp[num]!=0) return dp[num];
    int mx=0;
    for(int i=0;i<arr[num].before.size();i++){
        mx = max(mx,solve(arr[num].before[i]));
    }
    dp[num] = mx + arr[num].time;
    return dp[num];
}

int main(){
    ios_base::sync_with_stdio(false);
	cin.tie(0);
    
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> arr[i].time;
        int temp;
        while(true){
            cin >> temp;
            if(temp==-1) break;
            arr[i].before.push_back(temp);
        }
    }
    for(int i=1;i<=n;i++){
        cout << solve(i) << '\n';
    }
}


/*
    Approach: 
        Use top-down as we don't know if other buildings are constructed yet.
        Use memoization to reduce calculation. 
        As buildings can be constructed simultaneously, we don't wait.
        It means that buildings can be constructed right after required buildings are all constructed.
        dp[i] = arr[i].time + max(arr[i].before[0<=j<arr[i].before.size()]);

    Time Complexity:
        each node is visited once = O(N)
*/