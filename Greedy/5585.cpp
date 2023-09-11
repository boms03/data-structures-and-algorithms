#include<iostream>
#include<algorithm>
using namespace std;
int yen[6]={500,100,50,10,5,1};
int main(){
    int n;
    cin >> n;
    int cal = 1000-n;
    int cnt=0;
    for(int i=0;i<6;i++){
        int coin = cal/yen[i];
        if(coin>0){
            cnt+=coin;
        }
        cal%=yen[i];
    }
    cout << cnt << '\n';
}

/*
    Approach:
        Pick expensive coins as much as possible to reduce the number of total coins returned
    Time complexity:
        O(N)
*/
