#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n,m,c_w,b_w,ans;
vector<int>cr;
vector<int>box;

int main(){

    cin >> n;
    for (int i=0;i<n;i++){
        cin >> c_w;
        cr.push_back(c_w);
    }
    cin >> m;
    for (int i=0;i<m;i++){
        cin >> b_w;
        box.push_back(b_w);
    }

    sort(cr.begin(),cr.end(),greater<int>());
    sort(box.begin(),box.end(),greater<int>());

    if(box[0]>cr[0]){
        cout << -1 << '\n';
        return 0;
    }


    while(!box.empty()){
        ans++;
        for(int i=0;i<cr.size();i++){
            for(int j=0;j<box.size();j++){
                if(cr[i]>=box[j]){
                    box.erase(box.begin()+j);
                    break;
                }
            }
        }
    }
    cout << ans << '\n';
}

/*
    Approach:
        Sort box and crane vector in desending order.
        Assign each crane the heavest box it can handle.
        Output -1 if the weight of heavest box is larger than the weight of crane capable of
    Time complexity:
        O(NM)

*/