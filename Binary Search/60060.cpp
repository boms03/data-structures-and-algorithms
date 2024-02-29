#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    vector<string> arr[10001];
    vector<string> rev[10001];
    
    for(auto& w: words){
        arr[w.length()].push_back(w);
        reverse(w.begin(),w.end());
        rev[w.length()].push_back(w);
    }
    
    for(auto& a: arr){
        sort(a.begin(),a.end());
    }
    
    for(auto& r: rev){
        sort(r.begin(),r.end());
    }
    
    string s;
    string e;
    
    for(auto& q: queries){
        s = q;
        e = q;
        int pos1 = s.find_first_of('?');
        int pos2 = s.find_last_of('?');
        while(pos1<=pos2){
            s[pos1]='a';
            e[pos1]='z';
            pos1++;
        }
        int cnt = 0;
        if(q[0]!='?'){
            auto lb = lower_bound(arr[q.length()].begin(),arr[q.length()].end(),s);
            auto ub = upper_bound(arr[q.length()].begin(),arr[q.length()].end(),e);
            cnt=ub-lb;
        } else{
            reverse(s.begin(),s.end());
            reverse(e.begin(),e.end());
            auto lb = lower_bound(rev[q.length()].begin(),rev[q.length()].end(),s);
            auto ub = upper_bound(rev[q.length()].begin(),rev[q.length()].end(),e);
            cnt=ub-lb;
        }
        
        answer.push_back(cnt);
    }

    return answer;
}

/*
    Approach:
        Replace ?s with 'a' or 'z' to set lower bound and upper bound to count the number of string in between the range
        [!] If a query starts with ?, it should be reversed
            ex) if ??bc becomes aabc, it is reversed to cbaa , cbzz and find string in the range cbaa<=string<=cbzz
            The reason why it should be reversed is that the range aabc<=string<=zzbc does not require the string to have "bc"
                ex) aabd, which should not be counted, is in the range. So reversing process forcefully requires it.

    Time Complexity:
        M: # queries
        N: # all strings
        O(MlogN)

*/