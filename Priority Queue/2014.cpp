#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

int main() {
    int K, N;
    cin >> K >> N;
    
    vector<int> primes(K);
    priority_queue<int, vector<int>, greater<int>> pq;
    set<int> visit;
    
    for (int i = 0; i < K; i++) {
        cin >> primes[i];
        pq.push(primes[i]);
        visit.insert(primes[i]);
    }

    int result = 0;

    for (int i = 0; i < N; i++) {
        result = pq.top();
        pq.pop();

        for (int j = 0; j < K; j++) {
            long long next = (long long)result * primes[j];

            if (next >= (1 << 31) - 1) continue;
            if (visit.find(next) != visit.end()) continue;

            pq.push(next);
            visit.insert(next);

            if (result % primes[j] == 0) break;
        }
    }
    
    cout << result << '\n';
}
