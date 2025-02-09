#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L;
    cin >> N >> L;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    deque<int> dq;
    for (int i = 0; i < N; i++) {
        if (!dq.empty() && dq.front() < i - L + 1) {
            dq.pop_front();
        }

        while (!dq.empty() && arr[dq.back()] >= arr[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        cout << arr[dq.front()] << " ";

    }
}
