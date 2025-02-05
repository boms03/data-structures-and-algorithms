#include<iostream>
#include<vector>
using namespace std;

int learned = 0;
int n,k;
vector<int>words;
int ans = 0;

void btk(int cur_idx,int cnt_learned){
    if(cnt_learned == k){
        int cnt = 0;
        for(int i=0;i<words.size();i++){
            if((learned & words[i]) == words[i]) cnt++;
        }
        ans = max(ans,cnt);
        return;
    }
    for(int i=cur_idx; i<26;i++){
        if((learned >> i) & 1) continue;
        learned |= 1 << i; 
        btk(i+1,cnt_learned+1);
        learned &= ~(1 << i); 
    }
}
int main(){
    cin >> n >> k;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        int s_to_i = 0;
        for(int j=0;j<s.size();j++){
            s_to_i |= 1 << (s[j]-'a'); 
        }
        words.push_back(s_to_i);
    }
    k = k-5;
    if(k<0){
        cout << 0 << '\n';
    } else{
        learned |= 1 << ('a'-'a');
        learned |= 1 << ('n'-'a');
        learned |= 1 << ('t'-'a');
        learned |= 1 << ('i'-'a');
        learned |= 1 << ('c'-'a');
        btk(0,0);
        cout << ans << '\n';
    }
}