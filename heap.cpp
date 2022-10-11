#include <iostream>
using namespace std;

class Node{
    public:
    Node* left;
    Node* right;
    Node* parent;
    int value;
    Node(int v){
        value = v;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class DecreasingHeap{
    public:
    DecreasingHeap(){}

    bool is_empty(){
           return root==nullptr;
        }

    void add(int value){
        add(root,value);
    }


    private:
    Node* root = nullptr;
    int length = 0;
    void add(Node* temp,int value){
            if(is_empty()){
                root = new Node(value);
                length++;
            }else if(value<=temp->value){
                if(temp->left!=nullptr){
                    add(temp->left, value);
                }else{
                    temp->left = new Node(value);
                    temp->left->parent=temp;
                    length++;
                }
            }else if(value > temp->value){
                if(temp->right!=nullptr){
                    add(temp->right, value);
                }else{
                    temp->right = new Node(value);
                    swap(temp,temp->right);
                    temp->right->parent=temp;
                    length++;
                }
            }
    }
    void swap(Node* &a, Node* &b){
        Node* temp = a;
        a = b;
        b = temp;
    }
};