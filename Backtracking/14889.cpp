#include<iostream>
#include<cmath>
using namespace std;

bool check[22];
int n;
int map[22][22];
int ans = 1e9;

void btk(int idx, int cnt){
    if(cnt==n/2){ 
        int sum1 =0;
        int sum2 =0;
        for(int i=1;i<=n;i++){ 
            for(int j=i+1;j<=n;j++){
                if(check[i] && check[j]){
                    sum1+=map[i][j];
                    sum1+=map[j][i];
                } else if(!check[i] && !check[j]) {
                    sum2+=map[i][j];
                    sum2+=map[j][i];
                }
            }
        }
        ans = min(ans,abs(sum1-sum2));
        return;
    }

    for (int i=idx; i<=n; i++){
        if(check[i]==true) continue;
        check[i]=true;
        btk(i,cnt+1);
        check[i]=false;
    }

}
int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> map[i][j];
        }
    }
    btk(1,0);
    cout << ans << '\n';

}

/*
    Approach:   
        Use backtracking to create a n/2 combination to create team1 and team2.
        Calculate only once (team 123 == team 321) to avoid time limit exceed.
        To do this, use idx to remember the last number picked so that same team but in different order does not occur.
        for (int i=idx; i<=n; i++) vs for (int i=1; i<=n; i++).
    Time Complexity: 
        backtracking: smaller than nCn/2
        calculation: n^2 / 2
        O(nCn/2*n*n)
*/