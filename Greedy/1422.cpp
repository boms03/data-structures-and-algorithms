#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int n,k;
string input,mx;
vector<string>v;
vector<string>sv;


bool cmp(string a, string b){
    if(a+b>b+a){
        return true;
    }
    return false;
}
int main(){
    cin >> k >> n;
    for(int i=0;i<k;i++){
        cin >> input;
        if(input.size()>mx.size()||(input.size()==mx.size() && input > mx)) mx=input;
        v.push_back(input);
    }

    for(int i=0;i<n-k;i++){
        v.push_back(mx);
    }


    sort(v.begin(),v.end(),cmp);

    for(int i=0;i<v.size();i++){
        cout << v[i];
    }
}


/*
    Approach:
        If I have to choose every element at least once, I would choose the largest number multiple times afterward.
        ex) 3 elements and pick 5: 1,20,300 300 300 (5-3 times more 300)
        Now sort 1,20,300 300 300 by comparing a+b and b+a (index a<b).
        Swap if b+a>a+b

    Time complexity:
        O(nlogn)

*/