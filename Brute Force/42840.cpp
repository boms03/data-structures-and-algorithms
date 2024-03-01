#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int>ans;
    vector<int>one={1, 2, 3, 4, 5};
    vector<int>two={2, 1, 2, 3, 2, 4, 2, 5};
    vector<int>three={3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    int cnt1=0,cnt2=0,cnt3=0;

    for(int i=0;i<answers.size();i++){
        if(answers[i]==one[i % one.size()]) cnt1++;
        if(answers[i]==two[i % two.size()]) cnt2++;
        if(answers[i]==three[i % three.size()]) cnt3++;
    }

    int mx=0;
    mx=max(cnt1,max(cnt2,cnt3));
    if(cnt1==mx) ans.push_back(1);
    if(cnt2==mx) ans.push_back(2);
    if(cnt3==mx) ans.push_back(3);

    return ans;
    
}

/*
    Approach:
        Match indexes of 3 different vectors to 1 vector.
        In a for loop, i % vector.size() circulates in a range [0,vector.size()-1]
    Time Complexity:
        O(N)
*/