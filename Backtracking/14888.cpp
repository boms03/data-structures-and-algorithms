#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N;
vector<char>v;
int num[12];
int cpy[12]; // copy of num
int ans[12]; // subsequence of indexes of operators
int chk[12];
int operators[4];
int mx = -1e9;
int mn = 1e9;

// void btk(int nx){
//     if(nx==v.size()){
//         int calc = num[0];

//         for(int i=0;i<N-1;i++){ // calculate in the order of subsequence
//             if(v[ans[i]]=='+'){
//                 calc+=num[i]+num[i+1];
//             } else if (v[ans[i]]=='-'){
//                 calc=num[i]-num[i+1];
//             } else if (v[ans[i]]=='*'){
//                 calc=num[i]*num[i+1];
//             } else {
//                 calc=num[i]/num[i+1];
//             }
//             num[i+1]=calc;
//         }
//         mx=max(mx,calc);
//         mn=min(mn,calc);
        
        
//     }

//     for(int i=0;i<v.size();i++){ // create all subsequence of arithmetic operators
//         if(chk[i]) continue;
//         chk[i]=1;
//         ans[nx]=i;
//         btk(nx+1);
//         chk[i]=0;
//         ans[nx]=-1;
//     }
// }

void btk(int result, int idx){
    if(idx==N){
        mx=max(mx,result);
        mn=min(mn,result);
        return;
    }
    for(int i=0;i<4;i++){ // check all subsequence of arithmatic operators (initial subsequence: + - * /)
        if(operators[i]>0){
            operators[i]--;
            if(i==0){
                btk(result+num[idx],idx+1);
            } else if (i==1){
                btk(result-num[idx],idx+1);
            } else if (i==2){
                btk(result*num[idx],idx+1);
            } else {
                btk(result/num[idx],idx+1);
            }
            operators[i]++;
        }
    }
}

int main(){
    cin >> N;
    for(int i=0; i<N;i++){
        int a;
        cin >> a;
        num[i] = a;
        cpy[i] = a;
    }
    for (int i=0; i<4;i++){
        cin >> operators[i];
    }

    btk(num[0],1); // begin by using operator to the first number
    cout << mx << endl;
    cout << mn << endl;
}