#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
int N;
int prime[4000001];
vector<int>psum;
int main(){
    cin >> N;

    /*
    sieve of eratosthenes
    starting from 2, multiples of number cannot be prime
    eliminate multiples of 2,3,4(already gone),5,6(already gone),7....
    */
    for (int i=2;i<=N;i++){
        for (int j=2*i;j<=N;j+=i){
            prime[j]=1;
        }
    }

    //when one partial sum alone can be an answer ex. 41: 41-0
    psum.push_back(0);

    int sum=0;
    for (int i=2;i<=N;i++){
        if(prime[i]==1) continue;
        sum+=i;
        psum.push_back(sum);
    }

    int ans=0;
    int l =0;
    int r =0;
    while(l<=r&&r<psum.size()){
        if(psum[r]-psum[l]==N){
            ans++;
            r+=1; // find larger prime number
        } else if (psum[r]-psum[l]>N){
            l+=1;
        } else { 
            r+=1;
        }
    }
    cout << ans << endl;

}

/*
    sieve of eratosthenes O(nlog(logn))
    two pointers O(N)
*/