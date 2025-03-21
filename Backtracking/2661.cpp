#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string>
using namespace std;
int N;

bool check(string tmp, int size){
    for(int i=1;i<=size/2;i++){
        string f = tmp.substr(size-i,i);
        string s = tmp.substr(size-2*i,i);
        if(f.compare(s) == 0) return false;
    }
    return true;
}
void btk(string tmp,int idx){ // tmp: memoization of sequence with length of idx-1 
    if(idx==N){
        cout << tmp << endl;
        exit(0);
    }
    if(!check(tmp,idx)){
        return;
    }

    btk(tmp+"1",idx+1);
    btk(tmp+"2",idx+1);
    btk(tmp+"3",idx+1);

}
int main(){
    cin >> N;
    btk("",0);
}

// O(N^2)
