#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
typedef struct{
    int n;
    int s;
    int b;
} guesses;
vector<guesses>g;
bool num[1000];

void find(){
    for(int i=0;i<g.size();i++){
        for(int j=123;j<=999;j++){
            if (!num[j]) continue;
            string comp = to_string(j);
            string guess = to_string(g[i].n);
            int strike = 0;
            int ball = 0;
            for(int z=0; z<3;z++){
                for(int k=0; k<3;k++){
                    if(comp[z]==guess[k] && z==k) strike++;
                    if(comp[z]==guess[k] && z!=k) ball++;
                }
            }
            if (strike!=g[i].s || ball!=g[i].b) num[j]=false;
        }
    }

}
int main(){
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        int a,b,c;
        cin >> a >> b >> c;
        g.push_back({a,b,c});
    }
    memset(num,true,sizeof(num));
    for(int j=123;j<=999;j++){
        string comp = to_string(j);
        if(comp[0]==comp[1] || comp[0]==comp[2] || comp[1]==comp[2]) num[j]=false;
        if(comp[0]-'0'==0 || comp[1]-'0'==0 || comp[2]-'0'==0) num[j]=false;
    }

    find();

    int ans;
    for(int i=123;i<=999;i++){
        if(num[i]){
            ans++;
        }
    }
    cout << ans <<'\n';
}