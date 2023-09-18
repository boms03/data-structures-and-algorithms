#include<iostream>
#include<algorithm>
using namespace std;

int n;
bool flag = true;

void btk(int prev, int cnt){
    if (cnt==n){    
        cout << prev << '\n';
        return;
    }
    for (int i=0;i<=9;i++){
        if ((i==1||i==0)&&cnt==0) continue;
        for(int j=2;j<prev*10+i;j++){ // check prime number
            if ((prev*10+i)%j==0){
                flag=false; 
                break;
            } else {
                flag=true;
            }
        }
        if (flag) btk(prev*10+i, cnt+1);
    }
}

int main(){
    cin >> n;
    btk(0,0);
}

/*
    Approach:
        Backtrack until a number length of n is found.
        Everytime a digit is added to a number, it has to be a prime number.
        1) 0 and 1 are impossible when the length is 1.
        2) prev*10+i is a possible prime number.
            1) check if it is a prime number by dividing it by 2~prev*10+i-1
        3) keep updating prev by prev*10+i to keep adding digit at the next recurrence.
*/