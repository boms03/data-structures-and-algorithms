#include<iostream>
#include<string>
using namespace std;
string s;
string temp="";
bool neg=false;
int ans = 0;
int main(){
    cin >> s;
    for(int i=0;i<=s.size();i++){

        if(s[i]=='+' || s[i]=='-' || s[i]=='\0'){
            if(neg){ // inside minus bracket
                ans-=stoi(temp);
            } else{
                ans+=stoi(temp);
            }
            temp="";

            if(s[i]=='-'){ // beginning of minus bracket
                neg = true;
            }
        }
        else {
            temp+=s[i];
        }
    }
    cout << ans << endl;
    
}

/*
    Approach:
        At an operator's turn, check if it is currently inside minuns bracket and calculate

        1. Calculate when +,-,or\0 found
            1. if it is inside - bracket, subtract the number in temp string.
            2. if - is found, indicate the beginning of minus bracket.
        2. Store a digit in the temp string if +,-,nor \0.

    Time Complexity:
        O(N)
*/