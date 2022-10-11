#include <iostream>
#include <set>
#include <vector>

using namespace std;



int main(){
    vector<int> v {10,45,19,13,26,97,5,3,2,1};
    set<int> s;
    for(auto i:v){
        bool isprime = true;
        int m = i/2;
        for (int j = 2; j <= m; j++)
        {
            if(i%j==0){
                isprime = false;
                break;
            }
        }
        if(isprime && i!=1){
            s.insert(i);
        }
    }
    for(auto x:s){
        cout<<x<<endl;
    } 

    return 0;
}