#include <iostream>
using namespace std;

class Mathem{
    public:
    static float PI;
    static float e;
    
    static void shaker_sort(int a[], int length){
        bool flag = true;
        while(flag){
            flag = false;
            --length;
            for(int i = 0; i<length; ++i){
                if(a[i]>a[i+1]){
                    int temp = a[i];
                    a[i] = a[i+1];
                    a[i+1] = temp;
                    flag = true;
                }
            }
        }
    }

    static int square(int a){
        return a*a;
    }

    static float circle(int radius){
        return PI*square(radius);
    }
};
float Mathem::PI = 3.14;
float Mathem::e = 2.71;

int main(){
    int arr[] = {3,6,8,9,-256,45};
    Mathem::shaker_sort(arr,6);
    for (int i = 0; i < 6; i++)
    {
        cout<<arr[i]<<endl;
    }
    
    cout<<"Area of Circle is "<<Mathem::circle(4)<<endl;
    cout<<"Area of Square is "<<Mathem::square(5)<<endl;

}