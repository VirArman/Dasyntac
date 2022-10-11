#include <iostream>
using namespace std;

class Income{
    public:
    double shop;
    double advertisement;
    double apps;
    double service;
    double traiding;

    Income(){}
    Income(double shop,  double advertisement, double apps, double service, double traiding){
        this->shop = shop;
        this->advertisement = advertisement;
        this->apps = apps;
        this->service = service;
        this->traiding = traiding;
    }
    double total(){
        return shop+advertisement+apps+service+traiding;
    }

    Income& operator= (const Income& temp){
        
        this->shop = temp.shop;
        this->advertisement = temp.advertisement;
        this->apps = temp.apps;
        this->service = temp.service;
        this->traiding = temp.traiding;
        return* this;
    }

    bool operator== (const Income& temp){
        if(this==&temp){
            return true;
        }
        bool flag = shop == temp.shop && 
        advertisement == temp.advertisement && 
        apps == temp.apps && 
        service == temp.service && 
        traiding == temp.traiding;
        return flag;
    }
    bool operator!= (const Income& temp){
        bool flag = shop == temp.shop && 
        advertisement == temp.advertisement && 
        apps == temp.apps && 
        service == temp.service && 
        traiding == temp.traiding;
        return !flag;
    } 
    bool operator> (Income& temp){
       
        return this->total() > temp.total();
    }
    bool operator< ( Income& temp){

        return this->total() < temp.total();
    }
    bool operator>= (Income& temp){

        return this->total() >= temp.total();
    }
    bool operator<= (Income& temp){

        return this->total() <= temp.total();
    }

    const Income operator+ (const Income x){
        Income temp;
        temp.shop = shop + x.shop;
        temp.apps = apps + x.apps;
        temp.advertisement = advertisement + x.advertisement;
        temp.service = service + x.service;
        temp.traiding = traiding + x.traiding;
        return temp;
    }
    const Income& operator+= (const Income x){
        shop = shop + x.shop;
        apps = apps + x.apps;
        advertisement = advertisement + x.advertisement;
        service = service + x.service;
        traiding = traiding + x.traiding;
        return* this;
    }    
    const Income operator* (const Income x){
        Income temp;
        temp.shop = shop * x.shop;
        temp.apps = apps * x.apps;
        temp.advertisement = advertisement * x.advertisement;
        temp.service = service * x.service;
        temp.traiding = traiding * x.traiding;
        return temp;
    }
    const Income& operator*= (const Income x){
        shop = shop * x.shop;
        apps = apps * x.apps;
        advertisement = advertisement * x.advertisement;
        service = service * x.service;
        traiding = traiding * x.traiding;
        return* this;
    }     
    const Income operator/ (const Income x){
        Income temp;
        temp.shop = shop / x.shop;
        temp.apps = apps / x.apps;
        temp.advertisement = advertisement / x.advertisement;
        temp.service = service / x.service;
        temp.traiding = traiding / x.traiding;
        return temp;
    }
    const Income& operator/= (const Income x){
        shop = shop / x.shop;
        apps = apps / x.apps;
        advertisement = advertisement / x.advertisement;
        service = service / x.service;
        traiding = traiding / x.traiding;
        return* this;
    }     
    const Income operator- (const Income x){
        Income temp;
        temp.shop = shop - x.shop;
        temp.apps = apps - x.apps;
        temp.advertisement = advertisement - x.advertisement;
        temp.service = service - x.service;
        temp.traiding = traiding - x.traiding;
        return temp;
    }
    const Income& operator-= (const Income x){
        shop = shop - x.shop;
        apps = apps - x.apps;
        advertisement = advertisement - x.advertisement;
        service = service - x.service;
        traiding = traiding - x.traiding;
        return* this;
    } 
    Income operator++ (int a){
        std::cout<<"----------------Postfix--------------------"<<std::endl;
        Income temp = *this;
        this->advertisement++;
        this->apps++;
        this->traiding++;
        this->service++;
        this->shop++;
        return temp;
    }
    Income& operator++ (){
        std::cout<<"----------------Prefix--------------------"<<std::endl;

        this->advertisement++;
        this->apps++;
        this->traiding++;
        this->service++;
        this->shop++;
        return *this;
    }    
    Income operator-- (int a){
        std::cout<<"----------------Postfix--------------------"<<std::endl;
        Income temp = *this;
        this->advertisement--;
        this->apps--;
        this->traiding--;
        this->service--;
        this->shop--;
        return temp;
    }
    Income& operator-- (){
        std::cout<<"----------------Prefix--------------------"<<std::endl;

        this->advertisement--;
        this->apps--;
        this->traiding--;
        this->service--;
        this->shop--;
        return *this;
    }    
    friend ostream& operator<<(ostream& print, Income I){
        print<<"From Shop: "<<I.shop<<"\n";
        print<<"From Advertisment: "<<I.advertisement<<"\n";
        print<<"From Apps: "<<I.apps<<"\n";
        print<<"From Service: "<<I.service<<"\n";
        print<<"From Traiding: "<<I.traiding<<"\n";
        return print;
    }
    friend istream& operator>>(istream& input, Income I){
        cout<<"From Shop: ";
        input>>I.shop;
        cout<<"From Advertisment: ";
        input>>I.advertisement;
        cout<<"From Apps: ";
        input>>I.apps;
        cout<<"From Service: ";
        input>>I.service;
        cout<<"From Traiding: ";
        input>>I.traiding;
        return input;
    }
};
int main(){
    Income A(123.8,25,6,79,56);
    Income B(15.6,25.56,68.92,9.26,59.23);
    Income C(15.6,25.56,68.92,9.26,59.23);
    cout<<B<<endl;
    A=B;
    cout<<A<<endl;
    A++;
    ++A;
    cout<<A<<endl;
    cout<<(A!=C) <<endl;
    cout<<(C==B) <<endl;
    cout<<A+B<<endl;
    return 0;
}