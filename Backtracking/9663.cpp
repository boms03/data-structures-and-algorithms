#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<map>
#include<cstring>
using namespace std;

int n;
int col[16];
int answer=0;
bool flag=true;

void btk(int ny){
    if(ny==n) answer++;
    else {
        for(int x=0;x<n;x++){
            col[ny]=x;
            for(int i=0; i<ny; i++){
                if (col[i]==col[ny] || abs(ny-i)== abs(col[ny]-col[i])) flag=false;
            }
            if (flag) btk(ny+1);
            flag = true;
        }
    }
}
int main(){
    cin >> n;
    btk(0);
    cout << answer << endl;
}

