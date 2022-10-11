#include <iostream>
using namespace std;

int main(){
    int a = 0b11110101011010010101111101001111;
    unsigned int result = (a<<20)>>28;
    cout<<result<<endl;
    return 0;
}