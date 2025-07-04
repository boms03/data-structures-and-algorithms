#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;
vector<int>nums;
vector<int>ngf;
stack<int>stk;
unordered_map<int,int>freq;
int n;
int main() {
    ios_base::sync_with_stdio(false);  // 입출력 속도 향상
    cin.tie(NULL);
    cin >> n;
    nums.resize(n+1);
    ngf.resize(n+1,-1);
    for(int i=0;i<n;i++){
        cin >> nums[i];
        if(freq.find(nums[i])==freq.end()){
            freq[nums[i]]=1;
        } else{
            freq[nums[i]]+=1;
        }
    }
    stk.push(0);
    for(int i=1;i<n;i++){
        while(!stk.empty() && freq[nums[stk.top()]] < freq[nums[i]]){
            ngf[stk.top()] = nums[i];
            stk.pop();
        }
        stk.push(i);
    }
    
    for(int i=0;i<n;i++) cout << ngf[i] << " ";

    return 0;
}
