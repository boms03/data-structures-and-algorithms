#include<iostream>
using namespace std;
int map[100001][3];
int main(){
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> map[i][0] >> map[i][1] >> map[i][2];
    }
    
    int prev1 = map[0][0];
    int prev2 = map[0][1];
    int prev3 = map[0][2];
    int prev1_min = map[0][0];
    int prev2_min = map[0][1];
    int prev3_min = map[0][2];
        
    int cur1,cur2,cur3,cur1_min, cur2_min,cur3_min;
    for (int i=1;i<n;i++){
        cur1 = max(prev1,prev2) + map[i][0];
        cur2 = max(prev1,max(prev2,prev3)) + map[i][1];
        cur3 = max(prev2,prev3) + map[i][2];
        prev1 = cur1;
        prev2 = cur2;
        prev3 = cur3;
        
        cur1_min = min(prev1_min,prev2_min) + map[i][0];
        cur2_min = min(prev1_min,min(prev2_min,prev3_min)) + map[i][1];
        cur3_min = min(prev2_min,prev3_min) + map[i][2];
        prev1_min = cur1_min;
        prev2_min = cur2_min;
        prev3_min = cur3_min;
    }
    
    cout << max(prev1,max(prev2,prev3)) << " " << min(prev1_min,min(prev2_min,prev3_min)) << '\n';
}