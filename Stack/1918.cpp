#include <iostream>
#include <string>
#include <stack>
using namespace std;

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; 
}

int main() {
    stack<char> stk;
    string s;
    cin >> s;
    
    for(int i = 0; i < s.length(); i++) {
        char c = s[i];
        
        if('A' <= c && c <= 'Z') {
            cout << c;
        }
        else {
            if(c == ')') {
                while(!stk.empty() && stk.top() != '(') {
                    cout << stk.top();
                    stk.pop();
                }
                if(!stk.empty()) stk.pop();
            }
            else if(c == '(') {
                stk.push(c);
            }
            else {
                while(!stk.empty() && 
                      getPriority(stk.top()) >= getPriority(c)) {
                    cout << stk.top();
                    stk.pop();
                }
                stk.push(c);
            }
        }
    }
    
    while(!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
    return 0;
}