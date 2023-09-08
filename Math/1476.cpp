#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int e,s,m;
int ans=0;

void greedy(int a, int b, int c){
    ans++;
    if (a==e && b==s && c==m){
        cout << ans << endl;
        return;
    }
    else {
        a++;
        b++;
        c++;
        if(a>15)a=1;
        if(b>28)b=1;
        if(c>19)c=1;
        greedy(a,b,c);
    }
    
}
int main(){
    cin >> e >> s >> m;
    greedy(1,1,1);
}