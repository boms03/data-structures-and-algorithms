#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<map>
#include<cstring>
using namespace std;

typedef struct {
    int ind;
    int front;
    int single;
}info;

int n;
vector<string>ss;
map<char,info>sinfo;
map<int,char>map1;
int track[26];
int chk[11];
int prm[26];
int answer,mp;



void btk(int nx, int idx){
    if(nx==mp){
        int sum=0;
        int result=0;
        for(int i=0; i<ss.size();i++){
            for(int j=0; j<ss[i].length();j++){
                int val = prm[sinfo[ss[i][j]].ind];
                if (i==ss.size()-1){
                    result+= val * pow(10,ss[i].length()-j-1);
                } else{
                    sum+= val*pow(10,ss[i].length()-j-1);
                }
            }
        }
        if(sum==result){
            answer++;
        }
    }

    for(int i=0; i<10;i++){
        if(chk[i])continue;
        if(i==0 && sinfo[map1[idx]].front==1 && sinfo[map1[idx]].single==0){
            continue;
        }
        chk[i]=1;
        prm[idx]=i;
        btk(nx+1,idx+1);
        chk[i]=0;
        prm[idx]=0;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while(true){
        cin >> n;
        if(n==0) break;
        for(int i=0; i<n;i++){
            string s;
            cin>> s;
            ss.push_back(s);
            for(int j=0;j<s.length();j++){
                if(track[s[j]-'A']==0){
                    track[s[j]-'A']=1;
                    int fr=0;
                    int si=0;
                    if(j==0) fr=1;
                    if(s.length()==1) si=1;

                    info str;
                    str.front=fr;
                    str.single=si;
                    str.ind=mp;

                    sinfo[s[j]]=str;
                    map1[mp]=s[j];

                    mp++;
                }
            }
        }

        btk(0,0);
        cout << answer << '\n';

        mp=0;
        answer=0;
        map1.clear();
        ss.clear();
        memset(chk, 0, sizeof(chk));
        memset(prm, 0, sizeof(prm));
        memset(track, 0, sizeof(track));
    }
}