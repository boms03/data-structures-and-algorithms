#include<iostream>
#include<vector>
#include<string>
using namespace std;
int n,k;
vector<string>s;
int alpha[27];
int ans;
int mx=0;

int check(){
    ans = 0;
    bool canR;
    for(int i=0; i<s.size();i++){
        canR = true;
        for(int j=0; j<s[i].length(); j++){ // check if all alphabets in the word are learned
            if (alpha[s[i][j]-'a']==0){
                canR = false;
                break;
            }
        }
        if(canR) ans++;
    }
    return ans;
}
void btk(int next, int idx){
    if(idx==k){
        mx=max(mx,check());
        return;
    }
    for(int i=next;i<26;i++){
        if(alpha[i]) continue;
        alpha[i]=1;
        btk(i+1,idx+1);
        alpha[i]=0;
    }
}
int main(){
    cin >> n >> k;
    if(k<5){ // every word involves a,n,t,i,c meaning k = 5 is the minimum requirement 
        cout << 0 << endl;
        exit(0);
    }
    k-=5;
    alpha['a'-'a']=1;
    alpha['n'-'a']=1;
    alpha['t'-'a']=1;
    alpha['i'-'a']=1;
    alpha['c'-'a']=1;
    for(int i=0;i<n;i++){
        string ss;
        cin >> ss;
        s.push_back(ss);
    }
    btk(0,0);
    cout << mx << '\n';
}

/*
    N : number of words
    K : number of alphabets to learn
    L : length of words
    O((21)C(K-5)*N*L)
*/
