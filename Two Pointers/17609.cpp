#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N;
string s;

int check(int l, int r, int del){ // use recursion as both l+1,r and l,r+1 can work 
    while(l<=r){
        if(s[l]==s[r]){
            l++;
            r--;
        } else {
            if(del==0){
                del++;
                if(check(l+1,r,del)==0 || check(l,r-1,del) ==0) return 1; // return 1 after deleting one
                return 2; // return 2 if both need more deletion 
            } else{
                return 2; // need more than one deletion
            }
        }
    }
    return 0; // no deletion needed
}
int main(){
    cin >> N;
    while(N--){
        cin >> s;
        cout << check(0,s.length()-1,0) << endl;
    }
}

/*
    O(N)
*/