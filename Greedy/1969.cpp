#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int n,m,cnt=0;
string s = "";
string dna[1001];

void alphaOrder(int a, int t, int g, int c,int max){
    if(a==max) s+="A";
    else if(c==max) s+="C";
    else if(g==max) s+="G";
    else s+="T";
}

int main(){
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> dna[i];
    for(int i=0;i<m;i++){
        int a=0,t=0,g=0,c=0;
        for(int j=0;j<n;j++){
            if(dna[j][i]=='A') a++;
            else if(dna[j][i]=='T') t++;        
            else if(dna[j][i]=='G') g++;     
            else c++;     
        }
        int mx = max(a,max(t,max(g,c)));
        alphaOrder(a,t,g,c,mx);
        cnt+=n-mx;
    }
    cout << s << '\n' << cnt << '\n';
}

/*
    Approach:
        Check the same index of N strings at a time and find the most frequent alphabet.
        If multiple alphabets have the same frequency, choose according to the alphabetic order.
        To do this, compare the maximum frequency and the frequency of each alphabet using if else statement in the order of A->C->G->T.

    Time Complexity:
        O(NM)
*/