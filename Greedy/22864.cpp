#include <iostream>
#include <algorithm>
using namespace std;

int a,b,c,m;
int main(){
    int cnt_w=0, cnt_h=0,cnt_f=0;
    cin >> a >> b >> c >> m;
    while(true){
        if(cnt_h==24) break;

        if(cnt_f+a>m){
            if(cnt_f-c>=0) cnt_f-=c;
            else cnt_f=0;
        } else{
            cnt_w+=b;
            cnt_f+=a;
        }
        cnt_h++;
    }
    cout << cnt_w << '\n';

    /*
        Approach:
            Finding maximum wort loads means work as much as possible and rest when the fatigue is over the limit.
            Keep resting until the current fatigue + work fatigue is under the maximum fatigue.
            Repeat this processes.

            Or use this equation: Ax - C(24-x) <=M, find the maximum x, and calculate Bx
        Time Complexity:
            O(1)
    */
}