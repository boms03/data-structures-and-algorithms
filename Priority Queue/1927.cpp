#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

int tree[400000]; 
int n;
int last_idx = 0;

void add(int a) {
    tree[++last_idx] = a;
    int cur_idx = last_idx;
    
    while (cur_idx > 1) {
        if (tree[cur_idx] < tree[cur_idx / 2]) {
            swap(tree[cur_idx], tree[cur_idx / 2]);
            cur_idx /= 2;
        } else {
            break;
        }
    }
}

int pop() {
    if (last_idx == 0) return 0;  
    
    int top = tree[1]; 
    tree[1] = tree[last_idx];  
    tree[last_idx] = INT_MAX;  
    last_idx--; 
    
    int cur_idx = 1;
    
    while (cur_idx * 2 <= last_idx) {
        int left_child = cur_idx * 2;
        int right_child = cur_idx * 2 + 1;
        
        int smallest = cur_idx;
        
        // Find the smallest of the current node and its children
        if (left_child <= last_idx && tree[left_child] < tree[smallest]) {
            smallest = left_child;
        }
        
        if (right_child <= last_idx && tree[right_child] < tree[smallest]) {
            smallest = right_child;
        }
        
        // If the current node is the smallest, break
        if (smallest == cur_idx) {
            break;
        }
        
        // Swap the current node with the smallest child
        swap(tree[cur_idx], tree[smallest]);
        cur_idx = smallest;  // Move to the child index to continue the process
    }
    
    return top;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    fill(tree, tree + 400000, INT_MAX); 

    cin >> n; 
    for (int i = 0; i < n; i++) {
        int input;
        cin >> input;

        if (input == 0) {
            cout << pop() << '\n'; 
        } else {
            add(input);
        }
    }

}
