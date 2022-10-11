#include <iostream>
#include <ctime>
using namespace std;

class IndexOutOfBound{
    public:
        string cause;
        string solution;
        time_t when;
        IndexOutOfBound(string cause, string solution, time_t when){
            this->cause = cause;
            this->solution = solution;
            this->when = when;
        }
        void show(){
            cout<<"-------------------------"<<endl;
            cout<<"Cause : "<<cause<<endl;
            cout<<"Solution : "<<solution<<endl;
            cout<<"When : "<<ctime(&when)<<endl;

        }

};



void shaker_sort(int a[], int length){
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
class Stack{//stack with dinamic size
    private:
        int* p;
        int index = 0;
        int size = 5;
    public:

        Stack(){
            p = new int[size];
        }

        void push(int n){
            if(isfull()){
                int* temp = p;
                p = new int[size*2];
                for(int i = 0;i<size;i++){
                    p[i]=temp[i];
                }
                size = size*2;
            }
            p[index++]=n;
        }
        int pop(){
            return p[--index];
        }
        bool isempty(){
            if(index<=0){
                return true;
            }
            else{
                return false;
            }
        }
        bool isfull(){
            if(index>=size){
                return true;
            }
            else{
                return false;
            }
        }
        
        void get_size(int s){
            size = s;
        }

        
};

class Queue{//queue with dinamic size
    private:
        int* p;
        int size = 5;
        int index_push = 0;
        int index_pop = 0;
    public:
        
        Queue(){
            p = new int[size];
        }
        void push(int n){
                if(isfull()){
                int* temp = p;
                p = new int[size*2];
                for(int i = 0;i<size-1;i++){
                    p[i]=temp[i];
                }
                size = size*2;
            }
            
            p[index_push++]=n;
        }
        int pop(){
            int temp = index_pop;
            index_pop++;
            if(index_pop == index_push){
                index_pop=0;
                index_push=0;
            }
            
            
            return p[temp];
        }
        bool isempty(){
            return index_pop==size || index_push==0;
        }
        bool isfull(){
            return index_push==size;
        }
        
        int length(){
            return size;
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
                for (int i = 0; i <= index; i++){
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

class Map{
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int length = 0;
public:
    Map(){
       cout<<"Non argument constructor"<<endl; 
    }
    Map (Map& m){
            Node* temp = m.head;
            for (int i = 0; i < m.length; i++)
            {
                push_back(temp->key,temp->value);
                temp = temp->next;
            }
        }
    ~Map(){
            if(head != nullptr){
                while(head!=tail){ 
                    head=head->next;
                    delete head->prev; 
                }
                delete head;
            }
        }
    void push_front(int key, int value ){
            if(!find(key)){   
                Node* temp = new Node(key, value);
                
                if(head == nullptr){
                    head = tail = temp;
                }else{
                    temp ->next = head;
                    head-> prev =temp;
                    head = temp;
                }
                length++;
            }
        }
    void push_back(int key, int value){
            if(!find(key)){
                Node* temp = new Node(key,value);
                
                if(head == nullptr){
                    head = tail = temp;
                }else{
                    tail-> next = temp;
                    temp -> prev =tail;
                    tail = temp;
                }
                length++;
            }
        }
    void insert(int key,int value, int index){
            if(!find(key)){
                Node* inserted = new Node(key,value);
                Node* temp = head;
                if(is_empty()){
                    head = tail =inserted;
                }
                if(index==0){
                    push_front(key,value);
                }else if(index==length-1){
                    push_back(key,value);
                }else{
                    for (int i = 0; i <= index; i++){
                        temp=temp->next;
                    }
                    temp->prev->next=inserted;
                    inserted->prev=temp->prev;
                    temp->prev=inserted;
                    inserted->next=temp;
                }
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
    void print(){
            for(Node* temp = head;temp != nullptr;temp = temp-> next){
                cout<<temp->key<<":"<<temp->value<<" ";
            }
        }
    bool find(int key){
            Node* node = head;
            for(int i=0;i<length;i++){
                if(node->key==key){
                    return true;
                }
                node = node->next;
            }
            return false;
        }
    Node* get_node(int n){
            Node* node = head;
            for(int i=0;i<n;i++){
                node = node->next;
            }
            return node;
        }
    int operator[](int key){
            Node* node = head;
            while(node->key!=key){
                node = node->next;
            }
            return node->value;
        }
    bool is_empty(){
        return !head;
    }
    int size(){
        return length;
    }
    bool operator==(Map& second){
            if(length != second.size()){
                return false;
            }
            Node* temp1 = head;
            Node* temp2 = second.head;
            for (int i = 0; i < length-1; i++)
            {
                if(temp1->value!=temp2->value && temp1->key!=temp2->key){
                    return false;
                }
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            return true;
        }
    Map& operator=(Map& ll){
            Node* temp = head;
            for (int i = 0; i < length-1; i++)
            {
                temp = temp->next;
                ll.push_back(temp->key,temp->value);
            }
            return *this;
        }
};



