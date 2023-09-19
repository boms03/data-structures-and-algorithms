#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

string n;
int sum;
vector<int>v;

int main(){
    cin >> n;
    for(int i=0;i<n.size();i++){
        v.push_back(n[i]-'0');
        sum+=n[i]-'0';
    }
    sort(v.begin(),v.end(),greater<int>());
    if(v[n.size()-1]!=0 || sum%3!=0){
        cout << -1;
        return 0;
    } else {
        for(int i=0;i<n.size();i++){
            cout << v[i];
        }
    }
}

/*
    Approach:
        Multiples of 30 means divisble by 10 and 3.
        Digits must include 0 to be divisble by 10.
        Sum of each digits should be divisible by 3 as well.

    Time Complexity:
        O(NlogN)
*/