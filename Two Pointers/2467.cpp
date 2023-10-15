#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;
int N,sum;
vector<int>v;

int main(){
    cin >> N;
    for (int i=0;i<N;i++){
        int a;
        cin >> a;
        v.push_back(a);
    }
    sort(v.begin(),v.end());
    
    // two pointers
    int l = 0;
    int r = N-1;


    // track min
    int min = INT_MAX;
    int minL= l;
    int minR= r;

    while(l<r){
        sum=v[l]+v[r];
        if(abs(sum)<min){
            min=abs(sum);
            minL= l;
            minR= r;
        }
        if (sum==0) break;
        if (sum>0) r-=1; // need smaller positive number
        else l+=1; //need larger negative number
    }
    cout << v[minL] << " " << v[minR] << endl;
}

/*
    two pointer O(N)
*/