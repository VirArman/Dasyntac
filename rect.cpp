#include<iostream>
using namespace std;

class Rectangle{
    public:
    int width;
    int length;
    int area;
    int perimeter;
    
    Rectangle(int width, int length){
        this->width = width;
        this->length = length;
        area = width*length;
        perimeter = (width+length)*2;
    }
    friend ostream& operator<<(ostream& tpel, Rectangle rect){
        tpel<<"Length: "<<rect.length<<endl;
        tpel<<"Width: "<<rect.width<<endl;
        tpel<<"Area: "<<rect.area<<endl;
        tpel<<"Perimeter: "<<rect.perimeter<<endl;
        return tpel;
    }
};
template <class T>
class Comparator{
    virtual int hamematel(T a, T b){
        if(a > b){
            return 1;
        }else if(a < b){
            return -1;
        }
        return 0;
    }
};

class SortByArea : public Comparator<Rectangle>{
    int compare(Rectangle a, Rectangle b){
        if(a.area > b.area){
            return 1;
        }else if(a.area < b.area){
            return -1;
        }
        return 0;
    }
};

class SortByPerimeter : public Comparator<Rectangle>{
    int compare(Rectangle a, Rectangle b){
        if(a.perimeter > b.perimeter){
            return 1;
        }else if(a.perimeter < b.perimeter){
            return -1;
        }
        return 0;
    }
};

class SortByWidth : public Comparator<Rectangle>{
    int compare(Rectangle a, Rectangle b){
        if(a.width > b.width){
            return 1;
        }else if(a.width < b.width){
            return -1;
        }
        return 0;
    }
};
class SortByLength : public Comparator<Rectangle>{
    int compare(Rectangle a, Rectangle b){
        if(a.length > b.length){
            return 1;
        }else if(a.length < b.length){
            return -1;
        }
        return 0;
    }
};