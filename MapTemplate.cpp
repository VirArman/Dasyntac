#include <iostream>
using namespace std;

template <class Key, class Value>
class Node{
    public:
        Key key;
        Value value;
        Node* prev;
        Node* next;

        Node(){};
        
        Node(int k, int v){
            key = k;
            value = v;
            prev = nullptr;
            next = nullptr;
        }

};
template <class K, class V>
class Map{
private:
    Node<K,V>* head = nullptr;
    Node<K,V>* tail = nullptr;
    int length = 0;
public:
    Map(){
       cout<<"Non argument constructor"<<endl; 
    }
    Map (Map& m){
            auto temp = m.head;
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
    void push_front(K key, V value ){
            if(!find(key)){   
                auto temp = new Node<K,V>(key, value);
                
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
    void push_back(K key, V value){
            if(!find(key)){
                auto temp = new Node<K,V>(key,value);
                
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
    void insert(K key,V value, int index){
            if(!find(key)){
                auto inserted = new Node<K,V>(key,value);
                auto temp = head;
                if(is_empty()){
                    head = tail =inserted;
                }
                if(index==0){
                    push_front(key,value);
                }else if(index==length-1){
                    push_back(key,value);
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
        }
    V pop_back(){
            V x = tail->value;
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            
            length--;
            return x;
        }
    V pop_front(){
        V x = head->value;
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
            
        length--;
        return x;
    }
    V pop(int n){
        if(is_empty()){
            return -1;
        }
        if(n==0){
            return pop_front();
        }
        if(n==length-1){
            return pop_back();
        }
        auto temp = get_node(n);
        V x = temp->value;
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        delete temp;
        --length;
        return x;
    }
    void print(){
            for(auto temp = head;temp != nullptr;temp = temp-> next){
                cout<<temp->key<<":"<<temp->value<<" ";
            }
        }
    bool find(K key){
            auto node = head;
            for(int i=0;i<length;i++){
                if(node->key==key){
                    return true;
                }
                node = node->next;
            }
            return false;
        }
    auto get_node(int n){
            auto node = head;
            for(int i=0;i<n;i++){
                node = node->next;
            }
            return node;
        }
    V operator[](K key){
            auto node = head;
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
            auto temp1 = head;
            auto temp2 = second.head;
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
            auto temp = head;
            for (int i = 0; i < length-1; i++)
            {
                temp = temp->next;
                ll.push_back(temp->key,temp->value);
            }
            return *this;
        }
};
int main(){

    return 0;
}