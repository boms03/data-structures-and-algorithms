#include <iostream>
#include <climits>
#include <vector>
#include<algorithm>
using namespace std;
int n;
int arr[1000001]={0,};
vector<int>ans;
int cnt=0;

int main()
{
    cin >> n;
    for (int i=1;i<=n;i++){
        cin>>arr[i];
    }
    
    for(int i=1;i<=n;i++){
        if(ans.size()==0 || arr[i]>ans.back()){
            ans.push_back(arr[i]);
        }
        else{
            int index= lower_bound(ans.begin(),ans.end(),arr[i])-ans.begin();
            ans[index]= arr[i];
        }
    }
    cout << ans.size() << endl;

}

// O(nlogn)