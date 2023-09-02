#include<iostream>
#include<algorithm>
using namespace std;

int n,s;
int map[21];
int used[21];
int sum = 0;
int cnt=0;

// void bt(int nx,int x){
//     if (nx>n) return; // out of index
//     if (sum==s && nx!=0) { // size of subsequence cant be 0 when target sum is 0
//         cnt++;
//     }

//     for (int i=0; i<n;i++){
//         if(used[i] || x>i) continue;
//         used[i]=1;
//         sum+=map[i];
//         cout << map[i] << " ";
//         bt(nx+1,i); // check all possible subsequence
//         cout << endl;
//         // comeback and try next i
//         used[i]=0;
//         sum-=map[i];

//     }

// }

void bt(int x, int sm){
    if(x==n){ // out of bound
        if(sm==s){
            cnt++;
        }
        return; // return to the previous status
    }
    bt(x+1,sm);
    bt(x+1,sm+map[x]);
}
int main(){
    cin >> n >> s;
    for(int i=0; i<n; i++) cin >> map[i];
    // bt(0,0);
    bt(0,0);
    if (s==0) cnt--; // size of subsequence cant be 0 when target sum is 0
    cout << cnt << endl;
}

/*
    O(2^N)
*/