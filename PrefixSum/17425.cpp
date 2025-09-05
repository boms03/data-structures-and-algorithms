#include<iostream>
#define MAX_N 1000001
using namespace std;

int t,n;
long long factor[MAX_N];
long long prefix[MAX_N];

void find_factor(){
    for(int i=1;i<=MAX_N;i++){
        for(int j=i;j<=MAX_N;j+=i){
            factor[j]+=i;
        }
    }
}

void calc_prefix(){
    prefix[0]=0;
    for(int i=1;i<=MAX_N;i++){
        prefix[i]=prefix[i-1]+factor[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> t;
    find_factor();
    calc_prefix();
    while(t--){
        cin >> n;
        cout << prefix[n] << '\n';
    }
}