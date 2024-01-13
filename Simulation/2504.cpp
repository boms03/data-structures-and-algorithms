#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
using namespace std;

int main(){
    string s;
    stack<char> stk;
    cin >> s;
    int ans=0;
    int temp=1;
    for(int i=0;i<s.length();i++){
        if(s[i]=='('){
            temp*=2;
            stk.push('(');
        } else if(s[i]=='['){
            temp*=3;
            stk.push('[');
        } else if(s[i]==')'){
            if(stk.empty() || stk.top()!='('){
                ans=0;
                break;
            } else if(s[i-1]=='('){
                ans+=temp;
                temp/=2;
                stk.pop();
            } else{
                temp/=2;
                stk.pop();
            }
        } else if(s[i]==']'){
            if(stk.empty() || stk.top()!='['){
                ans=0;
                break;
            } else if(s[i-1]=='['){
                ans+=temp;
                temp/=3;
                stk.pop();
            } else{
                temp/=3;
                stk.pop();
            }
        } 
    }

    if(!stk.empty()) ans = 0;

    cout << ans << '\n';
}

/*
    Approach:
        [1] Use distribution rule to simplify the case.
        [2] (()[[]])([]) = 2*(2+3*3)+2*3= (2*2)+(2*3*3)+(2*3)
        [3] now the equation is expressed as additions of multiplications
        [4] how are the multiplications derived?
            - the answer variable records the answer and the temp variable calculates the current stage
            - only count the opening brackets ( or [ and push it into the stack
            - every ( *2 or [ *3 temp
            - every ) /2 or ] /3 temp
            - [!] only divide by 2 or 3 and pop the stack if the current char is closing bracket and the privious input is also a closing bracket
                - this is because it was all calculated when the first time closing bracket was met.
                - ex [[]] -> temp added to answer when the first ] met -> temp = 3*3 includes outer bracket as well
    Time Complexity:
        O(N)
*/


