#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int L,C;
vector<char> input;

void btk(int cur_size, int cur_idx, string cur_string){
    if (cur_size == L) {
        int vowel_count = 0;
        for (char c : cur_string) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowel_count++;
            }
        }
        int consonant_count = L - vowel_count;
        if (vowel_count >= 1 && consonant_count >= 2) {
            cout << cur_string << endl;
        }
        return;
    }
    for(int i=cur_idx;i<C;i++){
        btk(cur_size+1, i+1, cur_string+input[i]);
    }

}
int main(){
    cin >> L >> C;
    input.resize(C);
    for(int i=0;i<C;i++){
        cin >> input[i];
    }
    sort(input.begin(),input.end());
    btk(0,0,"");

}