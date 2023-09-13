#include <iostream>
#include <algorithm>
using namespace std;

int n,cnt;
int arr[1001];
int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    sort(arr,arr+n);
    cnt = arr[0];
    for(int i=1;i<n;i++){
        cnt+=arr[i-1]+arr[i];
        arr[i]+=arr[i-1];
    }
    cout << cnt << '\n';
}

/*
    Approach:
        Lining up the people in ascending order of withdrawl time can fastly eliminate people from the line.
        Record accumulative sum of withdrawl time to calculate the total time waited by the people.
    Time Complexity:
        O(nlogn)
*/