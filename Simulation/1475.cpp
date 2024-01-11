#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(){
    int set[10]={0,};
    int nset=0;
    string num;
    cin >> num;
    for(int i=0;i<num.length();i++){
        set[num[i]-'0']++;
    }

    bool used6, used9 = false;
    bool change = false;

    while(true){

        change = false;
        used6=false;
        used9=false;

        for(int i=0;i<10;i++){
            if(set[i]>0){
                change = true;

                if ((i==9) && used6 && used9) break; //f

                if(i==9 && used6==false){ //d
                    if(set[9]>1){
                        set[9]-=2;
                        used6=true;
                        used9=true;
                    } else {
                        set[9]--;
                        used9=true;
                    }
                } else if(i==9 && used6==true){ //e
                    set[9]--;
                    used9=true;
                } else if(i==6 && used9==false){ //b
                    if(set[6]>1){
                        set[6]-=2;
                        used6=true;
                        used9=true;
                    } else { //c
                        set[6]--;
                        used6=true;
                    }
                } else if(i==6 && used9==true){
                    set[6]--;
                    used6=true;
                } else { // a
                    set[i]--;
                }
            }
        }

        if(change==true) nset++;
        else break; 
    }

    cout << nset << '\n';
}

/*

    Approach:
        [1] Count the frequency of 0~9 digits in the input
        [2] While loop until all the frequency of digits are 0
        [3] For loop represents one set. Decrement the frequency upon the following conditions
            a. decrement by 1 if the digit is not 6 and 9 
            b. if the frequency of 6 is greater than one and 9 was not used in the same set, decrement by 2 using 6 and 9
            c. if the frequency of 6 is 1 decrement by 1 using 6 in the set
            d. if the frequency of 9 is greater than one and 6 was not used in the same set, decrement by 2 using 6 and 9
            e. if the frequency of 9 is 1 decrement by 1 using 9 in the set
            f. move to the next set when a searching digit is 9 but both 6 and 9 were used before
    Time Complexity:
        O(10*K) = O(K): k times of for loop

    Improvement:
        My approach is too complex. 
        Simplify using the fact that frequency A times of digit K (not 6,9) means K needs A number of sets.
        Just add the frequency of 6 and 9 and divide by 2 since these can replace each other
            a. if the sum is even -> sum/2 sets 
            b. if the sum is odd -> sum/2 + 1 sets
*/