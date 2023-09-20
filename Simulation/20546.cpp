#include<iostream>
using namespace std;

int n;
int stock[15];

int jun(){
    int cash = n;
    int buy = 0;
    for(int i=0;i<14;i++){
        if(cash>=stock[i]){
            buy += cash/stock[i];        
            cash = cash%stock[i];
        }
        
    }
    return cash+(buy*stock[13]);
}

int sung(){
    int cash = n;
    int buy = 0;
    int inc=1, dec=1;
    for(int i=1;i<14;i++){
        if(inc>=3){
            if(buy>0){
                cash+=buy*stock[i];
                buy=0;
            }
        }
        if(dec>=3){
            if(cash>=stock[i]){
                buy += cash/stock[i];        
                cash = cash%stock[i];
            }
        }

        if(stock[i]>stock[i-1]) inc++;
        else inc = 1;
        if(stock[i]<stock[i-1]) dec++;
        else dec = 1;
        if(stock[i]==stock[i-1]){
            inc=1;
            dec=1;
        }
    }

    return cash+(buy*stock[13]);

}
int main(){
    cin >> n;
    for(int i=0;i<14;i++) cin >> stock[i];
    if(jun()>sung()) cout << "BNP" << '\n';
    else if(jun()<sung()) cout << "TIMING" << '\n';
    else cout << "SAMESAME" << '\n';
}

/*
    Approach:
        Record increment and decrement of stock every day and buy or sell when more than 3 consecutive increments or decrements happened.
        Make sure no change in stock is not regarded increment nor decrement.
    Time Complexity:
        O(1)
*/