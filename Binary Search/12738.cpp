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
            int index= lower_bound(ans.begin(),ans.end(),arr[i])-ans.begin(); //O(logn)
            ans[index]= arr[i];
        }
    }
    cout << ans.size() << endl;

}

/*
    Approach:
        Keeping adding number if vector is blank or the number is bigger than the previous.
        If the number is smaller, replace with a number equal or greater in the vector.
        This means that the final vector does not give us the exact longest increasing sequence.
        But the length of longest increasing sequence is preserved as it is replacing with the next possible candidate in that position.
        (!)Works with negative number as well
    Time Complexity:
        N times iteration with binary search (lower_bound)
        O(nlogn)
*/