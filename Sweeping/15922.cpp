#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N;
int cnt=0;
vector< pair<int,int> >v;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i=0; i<N;i++){
        int a,b;
        cin >> a >> b;
        v.push_back({a,b});
    }
    sort(v.begin(),v.end()); // sort by the beginning to implement sweeping method

    // initial start and end of line
    int start = v[0].first; 
    int end = v[0].second;

    for(int i=1;i<N;i++){
        if (start<=v[i].first && v[i].first<=end){ // combine two line if the next start is in between the current start and end 
            if(v[i].second<=end) continue; // keep the current end;
            else end=v[i].second;
        } else {
            cnt += end-start; // count the current length if the next line doesn't intersect
            // restart recording with the next line
            start = v[i].first;
            end = v[i].second;
        }
    }
    // count the last remaining length
    cnt += end-start;
    cout << cnt << endl;
}

/*
    sweeping iterates the vector O(N)
*/