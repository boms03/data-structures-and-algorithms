#include<iostream>
using namespace std;
int n,m,ans;

int main(){
    cin >> n >> m;
    ans=1;
    if(n==1) ans = 1;
    else if(n==2){
        if(m < 3) ans=1;
        else if(m>=3&&m<7){
            if(m%2==0) ans+=m/2-1;
            else ans+= m/2;
        } else{
            ans=4;
        }
    } else {
        if(m<=4) ans=m;
        else if(m>4&&m<=6) ans=4;
        else ans=m-2;
    }
    cout << ans << '\n';
}

/*
    Approach:
        Option 1: 2 up, 1 right
        Option 2: 1 up, 2 right
        Option 3: 2 down, 1 right
        Option 4: 1 downn, 2 right
        The common condition is it moves the knight to the right side.
        It means that picking options that go to right by 1, not 2, as much as possible will make it go pass more chess squares.
        So before making 4 movements, move by repeating 1->4. Afterward, repeat 1->4=>2=>3.
    Time Complexity:
        O(1)
*/