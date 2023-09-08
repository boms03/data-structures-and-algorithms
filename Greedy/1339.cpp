#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int n;
int alpha[26];
int sum;

int main(){
    cin >> n;
    while(n--){
        string ss;
        cin >> ss;
        for(int i=0;i<ss.length();i++){
            alpha[ss[i]-'A']+=pow(10,ss.length()-i-1);
        }
    }
    sort(alpha,alpha+26,greater<>());
    int num=9; // 98765..... 
    for(int i=0;i<26;i++){
        if(alpha[i]==0) continue;
        else{
            sum+=alpha[i]*num--;
        }
    }
    cout << sum << endl;
}

// O(N)