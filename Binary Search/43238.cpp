#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;
    
    sort(times.begin(),times.end());
    long long  l = 1;
    long long  r = (long long) times[times.size()-1]*n;
    while(l<=r){
        long long mid = (l+r)/2;
        long long sum = 0;
        for(int i=0;i<times.size();i++){
            sum += mid/times[i];
        }
        if(sum>=n){
            r = mid - 1;
            answer = mid;
        } else {
            l = mid + 1;
        }
    }
    return answer;
}

/*
    Approach:
        Use parametric search to estimate the minimum time it takes to board everyone.
        [!] estimate/times[i] represents the number of people ith person can complete within the estimate time
    Time Complexity:
        O(logN)
*/