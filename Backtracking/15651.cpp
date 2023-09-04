#include<iostream>
#include<algorithm>
using namespace std;

int n,m;
int ans[9];

void btk(int idx){
    if(idx==m){
        for (int i=0; i<idx; i++) cout << ans[i] << " ";
        cout << '\n';
        return;
    }

    for(int i=1;i<=n;i++){ // no need to check as duplicates are allowed
        ans[idx]=i;
        btk(idx+1);
    }
}
int main(){
    cin >> n >> m;
    btk(0);
}