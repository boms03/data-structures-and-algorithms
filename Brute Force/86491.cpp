#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> sizes) {
    int w = 0, h = 0;
    for(auto& size: sizes){
        auto large = max(size[0],size[1]);
        auto small = min(size[0],size[1]);
        w = max(w,large);
        h = max(h,small); // maximum of minimum side length 
    }
    return w*h;
}

/*
    Approach:
        We need to find the minimum size of a wallet that can contain all the cards.
        We are given horizontal and vertical sizes, but direction does not matter as cards can be rotated!
        Iterate all the information and find the maximum side length and maximum of minimum side length 
    Time Complexity:
        O(N)
        
*/