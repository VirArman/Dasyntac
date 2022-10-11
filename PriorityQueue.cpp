#include<iostream>
using namespace std;

class Node{
    public:
        string key;
        int value;
        Node* prev;
        Node* next;
        
        Node(int x){
            value = x;
            prev = nullptr;
            next = nullptr;
        }
        Node(string k, int v){
            key = k;
            value = v;
            prev = nullptr;
            next = nullptr;
        }

};

class PriorityQueue{
    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        int length = 0;
    public:
        PriorityQueue(){
        }
        PriorityQueue(PriorityQueue& ll){
            Node* temp = ll.head;
            for (int i = 0; i < ll.length; i++)
            {
                temp = temp->next;
                ll.push_back(temp->key,temp->value);
            }
            
        }
        ~PriorityQueue(){
            if(head != nullptr){
                while(head!=tail){ 
                    head=head->next;
                    delete head->prev; 
                }
                delete head;
            }
        }

        PriorityQueue& operator=(PriorityQueue& ll){
            Node* temp = ll.head;
            for (int i = 0; i <ll.length; i++)
            {
                ll.push_back(temp->key,temp->value);
                temp = temp->next;
            }
            return *this;
        }

        void add(string key,int val){
            Node* inserted = new Node(key,val);
            
            if(is_empty()){
                head = tail =inserted;
                length++;
                return;
            }
            if(head->value > inserted->value){                 
                    push_front(key,val);
                    return;
                }else if(tail->value < inserted->value){
                    push_back(key,val);
                    return;
                }
            Node* temp = head;
            for(int i = 0; i<length; i++){
                if(temp->value > inserted->value){
                    insert(key,inserted->value,i-1);
                    return;
                }
                temp=temp->next;
            }
            
         }
        int operator[](int n){
            Node* node = head;
            for(int i=0;i<n;i++){
                node = node->next;
            }
            return node->value;
        }
        bool operator==(PriorityQueue& second){
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

        void print(){
            for(Node* temp = head;temp != nullptr;temp = temp-> next){
                cout<<temp->key<<":"<<temp->value<<endl;
            }
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
        bool find(string x){
            Node* node = head;
            for(int i=0;i<length;i++){
                if(node->key==x){
                    return true;
                }
                node = node->next;
            }
            return false;
        }
        int size(){
            return length;
        }
    private:     
    void push_back(string key, int value){
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
        
    void push_front(string key, int value ){
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

        
        bool is_empty(){
            return !head;
        }
        
        
        Node* get_node(int n){
            Node* node = head;
            for(int i=0;i<n;i++){
                node = node->next;
            }
            return node;
        }
    void insert(string key,int value, int index){
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
};

// int main(){
//     PriorityQueue p;
//     p.add("abc",21);
//     p.add("bcb",11);
//     p.add("ahsdi",-21);
//     p.add("asd",51);
//     p.add("dasd",26);
//     p.add("dddd",315);
//     p.print();
//     cout<<endl;
// }