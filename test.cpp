#include <iostream>
using namespace std;

void foo(int arr[]){
    arr[0] = 1;
}
int main(){
    int arr[] = {0,21,33};
    foo(arr);
    cout<<arr[0];
}