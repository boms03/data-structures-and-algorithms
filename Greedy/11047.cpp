#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
int coin[11];

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> coin[i];
    sort(coin, coin + n, greater<int>());
/*     int i = 0, sum = 0, cnt = 0;
    while (i < n)
    {
        if (sum + coin[i] <= k)
        {
            sum += coin[i];
            cnt++;
        }
        else
        {
            i++;
        }
    } */
    int total=0;
    int sum = k;
    for (int i=0;i<n;i++){
        int cnt = sum/coin[i];
        if (cnt>0){
            total+=cnt;
            sum%=coin[i]; // exchange remaining
        }
    }
    cout << total << endl;
}
/*
    Approach:
        Greedy: Minimum number of coins means picking expensive coins as much as possible to pick less coins.
        Sort the coin array in descending order.
        Starting from the most expensive coin, keep adding until the total sum reaches k.
        This problem assumes that all inputs will always produce K.
    Time complexity:
        Iterate each coin.
        O(N)
*/