#include <iostream>
#include <climits>
#include <vector>
using namespace std;
class Node{
    public:
        int key;
        int value;
        Node* prev;
        Node* next;
        
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

class PriorityQueue
{
    public:
        Node* head = nullptr;
        Node* tail = nullptr;
        
        ~ PriorityQueue()
        {
            if(head != nullptr) 
            {
                while(head != tail)      
                {
                    head = head -> next; 
                    delete head -> prev; 
                }
                delete head;             
            }
        }
        
        void push(int key, int value)
        {
            Node* temp = new Node(key, value);
            if(head == nullptr)
            {
                head = temp;
                tail = temp;
            }
            else if (temp->value < head->value)
            {
                head->prev = temp;
                temp->next = head;
                head = temp;
            }
            else
            {
                Node* iterator = head;
                while ((value >= iterator->value) && (iterator != tail))
                {
                    iterator = iterator->next;
                }
                if (iterator == tail && value >= tail->value)
                {
                    temp->prev = tail;
                    tail->next = temp;
                    tail = temp;
                }
                else
                {
                    iterator->prev->next = temp;
                    temp->next = iterator;
                    temp->prev = iterator->prev;
                    iterator->prev = temp;
                }
            }
        }
        Node pop()
        {
            if (head == nullptr) 
            {
                return -1;
            }
            else
            {
                Node tmp(head->key, head->value);
                Node* temp = head;
                if (head == tail) 
                {
                    head = tail = nullptr;
                    delete temp;
                    return tmp;
                }
                else
                {
                    head = head -> next;
                    head -> prev = nullptr;
                    delete temp;
                    return tmp;
                }
            }
            
        }
        void print() 
        { 
            Node* temp = head;        
            while(temp != nullptr)    
            {
                cout << temp->key << " : " << temp->value << endl;
                temp = temp->next;  
            } 
            cout << endl;          
        }
        
};

int main(){
    PriorityQueue pq;
    int const size = 9;
    int incidential[size][size] = {
        {0,5,0,0,0,0,45,0,15},
        {5,0,0,0,0,0,0,12,0},
        {0,0,0,20,0,60,0,0,0},
        {0,0,20,0,60,0,40,0,0},
        {0,0,0,60,0,0,0,30,0},
        {0,0,60,0,0,0,25,0,30},
        {45,0,0,40,0,25,0,70,0},
        {0,12,0,0,30,0,70,0,0},
        {15,0,0,0,0,30,0,0,0}
    };
    bool checkTable[size] ={0,0,0,0,0,0,0,0,0};
    string cities[size] = {"Ashtarak","Yerevan","Gyumri","Artashat","Yeghvard","Talin","Aparan","Abovyan","Oshakan"};
    int weights[size] = {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX};
    int lastChange[size] = {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX};
    int startIndex = INT_MAX;
    int dstIndex = INT_MAX;
    while(startIndex==INT_MAX && dstIndex==INT_MAX){
        cout<<"Enter start index"<<endl;
        cin>>startIndex;
        cout<<"Enter destination index"<<endl;
        cin>>dstIndex;
    }
    weights[startIndex] = 0;

    pq.push(startIndex,weights[startIndex]);
    int currentKey;
    int currentVal;
    while(pq.head!=nullptr){

        Node temp = pq.pop();
        currentKey = temp.key;
        currentVal = temp.value;
        for (int i = 0; i < size; i++)
        {
            bool notArrived = currentKey != dstIndex;
            bool isChecked = incidential[currentKey][i] && !checkTable[i];
            bool isShorter = (incidential[currentKey][i] + currentVal) < weights[i];
            if(notArrived && isChecked && isShorter){

                weights[i] = incidential[currentKey][i] + currentVal;
                pq.push(i, weights[i]);
                lastChange[i] = currentKey;
            }
        }
        checkTable[currentKey] = true;
        
    }
    cout << "The distance between " << cities[startIndex] << " and " << cities[dstIndex] << " is " << weights[dstIndex] << endl;

    int iterator = dstIndex;
    vector<string> way;
    while (iterator != INT_MAX)
    {
        way.push_back(cities[iterator]);
        iterator = lastChange[iterator];
        if (iterator != INT_MAX)
        {
            way.push_back(" -> ");
        } 
    }
    way.push_back("The optimal way is ");

    for (int i = way.size(); i > 0; --i)
    {
        cout << way[i - 1];
    }
    cout << endl;
    return 0;
}