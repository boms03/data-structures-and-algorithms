#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;


int main(){
    vector<int>v;
    map<int,int> freq;
    int n;
    double sum =0;
    int mx=-4000;
    int mn=4000;
    int mxf=0;

    cin >> n;
    for(int i=0;i<n;i++){
        int a;
        cin >> a;
        v.push_back(a);
        
        if(freq.find(a)==freq.end()){
            freq.insert(make_pair(a,1));
        } else{
            freq[a]++;
        }
        if(mxf<freq[a])mxf=freq[a];

        sum+=a;

        if(mx<a) mx=a;
        if(mn>a) mn=a;
    }
    sort(v.begin(),v.end());

    
    cout << (int) floor(sum/n+0.5) << '\n';
    cout << v[n/2] << '\n';

    vector<int>keys;

    for (auto iter : freq) {
	    if(iter.second==mxf) keys.push_back(iter.first);
    }

    sort(keys.begin(),keys.end());

    if(keys.size()>1){
        cout << keys[1] << '\n';
    } else{
        cout << keys[0] << '\n';
    }

    cout << mx-mn << '\n';

}

bool comp(const pair<int, int>& p1, const pair<int, int>& p2)
{
	if (p1.second == p2.second)
	{
		return p1.first < p2.first;
	}
	return p1.second > p2.second;

}


/*
    Approach:
        [1] Find Average
            - sum all the inputs
            - add +0.5 and floor
            - [!] use double rather than float as it has higher accuracy
        [2] Median
            - the number of inputs is guaranteed to be odd
            - index starts from 0 so the index of median is half the number of inputs
        [3] Mode
            - count the frequency using map and record the maximum mode number
            - [!] the condition says print the second smallest if there are more than 1 numbers with same mode
            - so move the maximum mode numbers to vector and sort in increasing order
            - vector[1] if there are more than 1 numbers with same mode
            - vector[0] if only one number with maximum mode
        [4] Range
            - subtract minimum from maximum
    
    Time Complexiy:
        O(N)
    
    Improvement:
        [3] Mode
            - my logic to find the second smallest number with maximum mode is too complex
            - moving elements from map to vector looks unnecessary
            - what if use vector<pair<>> and sort according to mode? -> how to sort according the second element of pair?
            - look at comp method

*/