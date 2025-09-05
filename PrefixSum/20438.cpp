#include<iostream>
#define MAX_M 5003
using namespace std;

int n,k,q,m;
int nums[MAX_M];
bool asleep[MAX_M];
int prefix_sum[MAX_M];

int main() {
    cin >> n >> k >> q >> m;
    int s;
    for(int i=0;i<k;i++){
        cin >> s;
        asleep[s]=true; 
    }
    for(int i=0;i<q;i++){
        cin >> s;
        if(!asleep[s]){
            for(int j=s; j<=n+2; j+=s){
                if (!asleep[j]) nums[j]=1;;
            }
        }
    }
    for(int i=3;i<=n+2;i++){
        prefix_sum[i]=prefix_sum[i-1];
        if(!nums[i]) prefix_sum[i]++;
    }

    for(int i=0;i<m;i++){
        int s,e;
        cin >> s >> e;
        cout << prefix_sum[e] - prefix_sum[s-1] << '\n';
    }
}
