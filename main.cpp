#include <iostream>
#include <ctime>
#include <useful.cpp>
using namespace std;
class IndexOutOfBound:public exception{
    public:
        string cause;
        string solution;
        time_t when;
        IndexOutOfBound(string cause, string solution, time_t when){
            this->cause = cause;
            this->solution = solution;
            this->when = when;
        }
        const char* what() const throw(){
            return "something";
        }
        void show(){
            cout<<"-------------------------"<<endl;
            cout<<"Cause : "<<cause<<endl;
            cout<<"Solution : "<<solution<<endl;
            cout<<"When : "<<ctime(&when)<<endl;

        }

};



class Node{
    public:
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(){};
        Node(int x){
            value = x;
            prev = nullptr;
            next = nullptr;
        }
        Node(int k, int v){
            key = k;
            value = v;
            prev = nullptr;
            next = nullptr;
        }

};


class LinkedList{
    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        int length = 0;
    public:
        LinkedList(){}
        LinkedList(LinkedList& ll){
            Node* temp = ll.head;
            for (int i = 0; i < ll.length; i++)
            {
                temp = temp->next;
                ll.push_back(temp->value);
            }
            
        }
        ~LinkedList(){
            if(head != nullptr){
                while(head!=tail){ 
                    head=head->next;
                    delete head->prev; 
                }
                delete head;
            }
        }

        LinkedList& operator=(LinkedList& ll){
            Node* temp = ll.head;
            for (int i = 0; i <ll.length; i++)
            {
                ll.push_back(temp->value);
                temp = temp->next;
            }
            return *this;
        }

        void insert(int x, int index){
            Node* inserted = new Node(x);
            Node* temp = head;
            if(is_empty()){
                head = tail =inserted;
                length++;
                return;
            }
            if(index==0){
                push_front(x);
            }else if(index==length-1){
                push_back(x);
            }else{
                for (int i = 0; i !=index; i++){
                    temp=temp->next;
                }
                temp->prev->next=inserted;
                inserted->prev=temp->prev;
                temp->prev=inserted;
                inserted->next=temp;
            }
         }
        void push_back(int x){
            Node* temp = new Node(x);
            
            if(head == nullptr){
                head = tail = temp;
            }else{
                tail-> next = temp;
                temp -> prev =tail;
                tail = temp;
            }
            length++;
        }
        
        void push_front(int x){
             Node* temp = new Node(x);
            
            if(head == nullptr){
                head = tail = temp;
            }else{
                temp ->next = head;
                head-> prev =temp;
                head = temp;
            }
            length++;
        }
        
        
        void print(){
            for(Node* temp = head;temp != nullptr;temp = temp-> next){
                cout<<temp->value<<" ";
            }
        }
        
        void print_reverse(){
            for(Node* temp = tail;temp != nullptr;temp = temp-> prev){
                cout<<temp->value<<" ";
            }
        }
        
        int pop_back(){
            int x = tail->value;
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            
            length--;
            return x;
        }
        int pop_front(){
            int x = head->value;
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            
            length--;
            return x;
        }
        int pop(int n){
            if(is_empty()){
                return -1;
            }
            if(n==0){
                return pop_front();
            }
            if(n==length-1){
                return pop_back();
            }
            Node* temp = get_node(n);
            int x = temp->value;
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            delete temp;
            --length;
            return x;
        }
        
        bool is_empty(){
            return !head;
        }
        bool operator==(LinkedList& second){
            if(length != second.size()){
                return false;
            }
            Node* temp1 = head;
            Node* temp2 = second.head;
            for (int i = 0; i < length-1; i++)
            {
                if(temp1->value!=temp2->value){
                    return false;
                }
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            return true;
        }
        int operator[](int n){
            if(n>=length){
                IndexOutOfBound x("The number is bigger than length","Write number from 0 to (length-1)",time(0));
                throw x;
            }
            Node* node = head;
            for(int i=0;i<n;i++){
                node = node->next;
            }
            return node->value;
            
        }
        Node* get_node(int n){
            Node* node = head;
            for(int i=0;i<n;i++){
                node = node->next;
            }
            return node;
        }
        bool find(int x){
            Node* node = head;
            for(int i=0;i<length;i++){
                if(node->value==x){
                    return true;
                }
                node = node->next;
            }
            return false;
        }

        void insertion_sort(){
            int temp;
            int n = 0;
            for (Node* a = head; a->next!=nullptr; a = a->next){
                if(a->value > a->next->value){
                    temp = a->next->value;
                    pop(n+1);
                    insert(temp,n);
                }
                n++;
            }
        }

        int size(){
            return length;
        }
};


int main()
{
    LinkedList ll;
    ll.push_back(12);
    ll.push_back(14);
    ll.push_back(13);
    ll.push_back(10);
    ll.push_back(11);
    ll.push_back(333);
    ll[168];
    ll.insertion_sort();
    ll.print();
    cout<<endl;
    return 0;
}