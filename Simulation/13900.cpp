#include<iostream>
using namespace std;

int n;
int arr[100001];
int psum[100001];

// int main(){
//     cin >> n;
//     for(int i=0;i<n;i++) cin >> arr[i];

//     long long sum = 0;
//     for(int i=0;i<n;i++){
//         for(int j=i+1;j<n;j++){
//             sum+=arr[i]*arr[j];
//         }
//     }
//     cout<< sum << '\n';
// } O(N^2)

int main(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> arr[i];
        if(i==0) psum[i]=arr[i];
        else psum[i]+=psum[i-1]+arr[i];
    }
    long long sum = 0;
    for(int i=0;i<n;i++){
        sum += arr[i]*(psum[n-1]-psum[i]);
    }
    cout << sum << endl;
}

/*
    First Approach:
        I used brute force search but it resulted in timeout as n <= 100000.
        O(N^2) time complexity does not satisfy this condition.
    Second Approach:
        I expressed the multiplications with addition as there are common divisors.
        For example, the input is (1,2,3,4)
        Sum of all possibible multiplications are (1*2+1*3+1*4) + (2*3+2*4) + (3*4)
        Then this can be expressed as 1*(2+3+4) + 2(3+4) + 3(4)
        This shows that I need to record partial sums: psum[]
        As a result, the equation is sum of ith * (psum[n-1]-psum[i])

    Time Complexity:
        O(N)
*/