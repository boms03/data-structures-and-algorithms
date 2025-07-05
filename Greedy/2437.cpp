#include <iostream>
#include <algorithm>
using namespace std;

int nums[1001];
int n;
int main() {
    cin >> n;
    for(int i=0;i<n;i++) cin >> nums[i];
    sort(nums,nums+n);
    
    int sum = 0;
    for(int i=0;i<n;i++){
        if(sum+1 < nums[i]) break;
        sum+=nums[i];
    }
    cout << sum+1;

    return 0;
}
