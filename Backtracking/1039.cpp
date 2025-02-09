#include <iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

int n, k;
set<pair<string, int>> visited; 
int ans = -1;

void btk(string num, int swap_cnt) {
    if (swap_cnt == k) {
        ans = max(ans, stoi(num));
        return;
    }
    
    for (int i = 0; i < num.size(); i++) {
        for (int j = i + 1; j < num.size(); j++) {
            if (i == 0 && num[j] == '0') continue; 
            
            swap(num[i], num[j]);
            
            if (visited.find({num, swap_cnt + 1}) == visited.end()) {
                visited.insert({num, swap_cnt + 1});
                btk(num, swap_cnt + 1);
            }
            
            swap(num[i], num[j]); 
        }
    }
}

int main() {
    cin >> n >> k;
    string num = to_string(n);
    
    btk(num, 0);
    
    cout << ans << endl;
    return 0;
}
