// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long MIN, MAX;
vector<bool>none_prime;
long long cnt;

void prime(){
    none_prime.resize(MAX-MIN+1,false);
    for(long long i=2;i*i<=MAX;i++){
        long long squared = i*i;
        long long start = ceil(double(MIN) / squared) * squared;
        for(long long j=start;j<=MAX;j+=squared){
            if(j>=MIN && !none_prime[j-MIN]){
                none_prime[j-MIN] = true;
                cnt++;
            }
            
        }
    }
}

int main() {
    cin >> MIN >> MAX;
    prime();
    // for(auto it = none_prime_set.begin(); it != none_prime_set.end(); ++it) {
    //     cout << *it << " ";
    // }
    // cout << endl;
    cout << MAX-MIN+1-cnt;
    return 0;
}
