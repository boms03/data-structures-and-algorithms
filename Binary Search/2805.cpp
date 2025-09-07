#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n,m;
int arr[1000001];

int ps(int s, int e) {
	int ans;
	while (s <= e) {
		long long mid = (s + e) >> 1;
		long long total = 0;
		for (int i = 0; i < n; i++) {
			if (arr[i] >= mid) total += arr[i]-mid;
		}
		if (total >= m) {
			ans = mid;
			s = mid + 1;
		} else if (total < m) {
			e = mid - 1;
		}
	}
	return ans;
}
int main() {
	cin >> n >> m;
	int max_height = 0;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		max_height = max(max_height, arr[i]);
	}
	cout << ps(1, max_height);
}
