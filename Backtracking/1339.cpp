#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;

int n;
int alpha[26];

bool comp(int a, int b){
    return a > b;
}

int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<s.size();j++){
            alpha[s[j]-'A']+=pow(10,s.size()-j-1);
        }
    }
    sort(alpha,alpha+26, comp);

    int num = 9;
    int sum = 0;
    for(int i=0; i<26; i++){
        if (!alpha[i]) continue;
        sum += alpha[i] * num;
        num--;
    }
    cout << sum;

}