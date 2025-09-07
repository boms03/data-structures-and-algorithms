#include <iostream>
#include <string>
#include <stack>
using namespace std;

int n;
int main() {
    stack<char>stk;
    string s;
    cin >> s;
    for(int i=0;i<s.length();i++){
        if('A'<=s[i] && s[i] <='Z') cout << s[i];
        else{
            if(s[i]==')'){
                while(!stk.empty() && stk.top()!='('){
                    cout << stk.top();
                    stk.pop();
                }
                stk.pop();
            }
            else if(s[i]=='(') stk.push(s[i]);
            else if(!stk.empty() && (stk.top()=='*' || stk.top()=='/')){
                cout << stk.top();
                stk.pop();
                stk.push(s[i]);
            } else if(!stk.empty() && (stk.top()=='+' || stk.top()=='-')){
                stk.push(s[i]);
            } else {
                stk.push(s[i]);
            }
        }
    }
    while(!stk.empty()){
        cout << stk.top();
        stk.pop();
    }
    return 0;
}
