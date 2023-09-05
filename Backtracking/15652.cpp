#include<iostream>
#include<algorithm>
using namespace std;

int n,m;
int ans[9];

void btk(int num, int idx){
    if(idx==m){
        for (int i=0; i<idx; i++) cout << ans[i] << " "; // [1]
        cout << '\n';
        return;
    }

    for(int i=num;i<=n;i++){ // no need to check as duplicates are allowed
        ans[idx]=i;
        btk(i,idx+1); // [2] i at idx+1 is greater or equal to i at idx-1
    }
}
int main(){
    cin >> n >> m;
    btk(1,0);
}

/*
    [1] N [2] N!
    O(N*N!)
*/