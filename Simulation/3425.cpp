#include<iostream>
#include<stack>
#include<string>
#include<vector>
using namespace std;

vector<string>op;
int n;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	bool total_flag = true;
	while (true) {
        op.clear();
		string opr;
        vector<long long> nums;
		while (true) {
			cin >> opr;
            if (opr == "END") {
                break;
            }
			if (opr == "QUIT") {
				return 0;
			}
			if (opr == "NUM") {
				long long x;
                cin >> x;
                nums.push_back(x);
			}
			op.push_back(opr);
		}

		cin >> n;

		for (int i = 0; i < n; i++) {
            stack<long long>stk;
			long long start;
			cin >> start;
			stk.push(start);

			int num_idx = 0;
			bool flag = true;
			for (int i = 0; i < op.size() && flag; i++) {
				if (op[i] == "NUM") {
					stk.push(nums[num_idx++]);
				}
				else if (op[i] == "POP") {
					if (stk.empty()) flag = false;
                    else stk.pop();
				}
				else if (op[i] == "INV") {
					if (stk.empty()) flag = false;
                    else {
                        long long top = stk.top();
                        stk.pop();
                        stk.push(-top);
                    }
				}
				else if (op[i] == "DUP") {
                    if (stk.empty()) flag = false;
                    else stk.push(stk.top());
                } 
				else if (op[i] == "SWP") {
					if (stk.empty() || stk.size() < 2) flag = false;
                    else {
						long long first = stk.top();
						stk.pop();
						long long second = stk.top();
						stk.pop();
						stk.push(first);
						stk.push(second);
					}
				}
				else if (op[i] == "ADD") {
					if (stk.empty() || stk.size()<2) flag = false;
                    else {
						long long first = stk.top();
						stk.pop();
					    long long second = stk.top();
						stk.pop();
						if (abs(first + second) > 1e9) flag = false;
						else stk.push(first + second);
					}
				}
				else if (op[i] == "SUB") {
					if (stk.empty() || stk.size()<2) flag = false;
                    else {
						long long first = stk.top();
						stk.pop();
					    long long second = stk.top();
						stk.pop();
						if (abs(second-first) > 1e9) flag = false;
						else stk.push(second-first);
					}
				}
				else if (op[i] == "MUL") {
					if (stk.empty() || stk.size()<2) flag = false;
                    else {
						long long first = stk.top();
						stk.pop();
					    long long second = stk.top();
						stk.pop();
						if (abs(second*first) > 1e9) flag = false;
						else stk.push(second*first);
					}
				}
				else if (op[i] == "DIV") {
					if (stk.empty() || stk.size() < 2) flag= false;
                    else {
						long long first = stk.top();
						if (first == 0) flag = false;
                        else {
                            stk.pop();
                            long long second = stk.top();
							stk.pop();
							if (second * first < 0 && !(first < 0 && second < 0)) {
								stk.push(-abs(second) / abs(first));
							}
							else {
								stk.push(abs(second) / abs(first));
							}
                        }
                    }
				}
				else if (op[i] == "MOD") {
					if (stk.empty() || stk.size() < 2) flag= false;
                    else {
						long long first = stk.top();
						if (first == 0) flag = false;
                        else {
                            stk.pop();
                            long long second = stk.top();
							stk.pop();
							if (second < 0) {
								stk.push(-abs(second) % abs(first));
							}
							else {
								stk.push(abs(second) % abs(first));
							}
                        }
                    }
				}
			}
			if (!flag || stk.size() != 1) cout << "ERROR\n";
            else cout << stk.top() << '\n';
		}
		cout << '\n';
	}
}