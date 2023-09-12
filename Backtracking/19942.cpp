#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

typedef struct{
    int p;
    int f;
    int s;
    int v;
    int price;
} option;

int n,mp,mf,ms,mv;
int mn = 1e9;
vector<option>options;
vector<int>col;
vector<int>ans;
bool flag = false;
void btk(int next, int sp, int sf, int ss, int sv, int sprice){ 
    if(sp>=mp && sf>=mf && ss>=ms && sv>=mv){ // minimum condition
        flag = true;
        if(sprice<mn){
            mn=sprice;
            ans=col;
        }
        return;
    }
    for (int i=next;i<options.size();i++){ // only backtrack options with greater index than previous index
        col.push_back(i+1); // add the current option index 
        btk(i+1,sp+options[i].p, sf+options[i].f, ss+options[i].s, sv+options[i].v, sprice+options[i].price);
        col.pop_back(); // remove the current option index as it will add the next option instead
    }
}
int main(){
    cin >> n;
    cin >> mp >> mf >> ms >> mv; 
    for (int i=0; i<n;i++){
        int a,b,c,d,e;
        cin >> a >> b >> c >> d >> e;
        options.push_back({a,b,c,d,e});
    }
    btk(0,0,0,0,0,0);
    if (flag){
        cout << mn << endl;
        for (int i=0;i<ans.size();i++) cout << ans[i] << " ";
        cout << '\n';
    } else { // couldn't reach the condition 
        cout << "-1" << '\n';
    }
}

/*
    backtracking 
    O(2^N)
*/