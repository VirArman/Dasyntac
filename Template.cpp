#include <iostream>
using namespace std;

template <class V>
class Node{
    public:
        V value;
        Node<V>* prev;
        Node<V>* next;
        Node(){};
        Node(V x){
            value = x;
            prev = nullptr;
            next = nullptr;
        }

};

template <class T>
class LinkedList{
    private:
        Node<T>* head = nullptr;
        Node<T>* tail = nullptr;
        int length = 0;
    public:
        LinkedList(){}
        LinkedList(LinkedList& ll){
            Node<T>* temp = ll.head;
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
            Node<T>* temp = ll.head;
            for (int i = 0; i <ll.length; i++)
            {
                ll.push_back(temp->value);
                temp = temp->next;
            }
            return *this;
        }

        void insert(T x, int index){
            Node<T>* inserted = new Node<T>(x);
            Node<T>* temp = head;
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
        void push_back(T x){
            Node<T>* temp = new Node<T>(x);
            
            if(head == nullptr){
                head = tail = temp;
            }else{
                tail-> next = temp;
                temp -> prev =tail;
                tail = temp;
            }
            length++;
        }
        
        void push_front(T x){
             Node<T>* temp = new Node<T>(x);
            
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
            for(Node<T>* temp = head;temp != nullptr;temp = temp-> next){
                cout<<temp->value<<" ";
            }
        }
        
        void print_reverse(){
            for(Node<T>* temp = tail;temp != nullptr;temp = temp-> prev){
                cout<<temp->value<<" ";
            }
        }
        
        T pop_back(){
            T x = tail->value;
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            
            length--;
            return x;
        }
        T pop_front(){
            T x = head->value;
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            
            length--;
            return x;
        }
        T pop(int n){
            if(is_empty()){
                return -1;
            }
            if(n==0){
                return pop_front();
            }
            if(n==length-1){
                return pop_back();
            }
            Node<T>* temp = get_node(n);
            T x = temp->value;
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
            Node<T>* temp1 = head;
            Node<T>* temp2 = second.head;
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
        T operator[](int n){
            Node<T>* node = head;
            for(int i=0;i<n;i++){
                node = node->next;
            }
            return node->value;
            
        }
        Node<T>* get_node(int n){
            Node<T>* node = head;
            for(int i=0;i<n;i++){
                node = node->next;
            }
            return node;
        }
        bool find(T x){
            Node<T>* node = head;
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
            for (Node<T>* a = head; a->next!=nullptr; a = a->next){
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
    LinkedList<string> ll;
    ll.push_back("asdsad");
    ll.push_back("dasd");
    ll.push_back("asdasd");
    ll.push_back("dadsad");
    ll.push_back("Asd");
    ll.push_back("dsad");
    ll.print();
    cout<<endl;
    LinkedList<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(4);
    l2.push_back(34);
    l2.print();
    cout<<endl;
    return 0;
}