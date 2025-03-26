#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int N,K;
vector<int>v;

int main(){
    cin >> N >> K;
    for (int i=0;i<N;i++){
        int a;
        cin >> a;
        v.push_back(a);
    }

    int sum=0;
    int start=0;
    int end=K-1;

    for (int i=start;i<=end;i++){ // first window
        sum += v[i];
    }

    int mx = sum;

    for (int i=1;i<N;i++){ 
        if(end+1>=N) break;
        // move window
        sum-=v[start]; 
        start++;
        sum+=v[end+1];
        end++;
        mx=max(mx,sum);
    }
    cout << mx << endl;

}

/*
    sliding window O(N)
*/

