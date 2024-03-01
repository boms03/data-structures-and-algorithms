#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>

using namespace std;

bool prime(int x){
    
    if(x < 2) return false;
    
    for(int i=2;i<=sqrt(x);i++){
        if(x%i==0) return false;
    }
    return true;
}

int solution(string numbers) {
    
    int answer = 0;
    set<int>ans;
    
    sort(numbers.begin(),numbers.end());
    
    do{
        string temp;
        for(int i=0;i<numbers.size();i++){
            temp+=numbers[i];
            if(prime(stoi(temp))) ans.insert(stoi(temp));
        }
    } while (next_permutation(numbers.begin(),numbers.end()));


    return ans.size();
}

/*
    Approach:
        Try dividing a number by range of 2 to sqrt(number) to determine prime number.
        Use set to avoid duplicates.
        (!) next_permutation generates permuations of a container
            - use do while structure
    Time Complexity:
        O(N!)

*/