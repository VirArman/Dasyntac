#include <iostream>
using namespace std;
template <class V>
class Node{
    public:
    V value;
    Node<V>* left;
    Node<V>* right;
    Node<V>* parent;
    Node(V v){
        value = v;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

template <class T>
class BinarySearchTree{
    private:
       Node<T>* root = nullptr;
       int length = 0;
    public:
        BinarySearchTree(){}
        BinarySearchTree(BinarySearchTree& BST){
            copy(BST.root);
        }
        ~BinarySearchTree(){
            DestRec(root);
        }
        BinarySearchTree(BinarySearchTree&& temp){
            this->root = temp.root;
            temp.root = nullptr;
        }
        bool is_empty(){
           return root==nullptr;
        }
        void add(T value){
            addRec(root, value);
        }
        void print(){
            printRec(root);
        }
        
        bool find(T value){
            return findRec(root, value);
         }
        BinarySearchTree& operator=(const BinarySearchTree& temp){
            if(this == &temp){
                return* this;
            }
            if(!is_empty()){
                DestRec(root);
            }
            root = nullptr;
            copy(temp.root);
            return* this;
       }
       bool operator==(BinarySearchTree& temp){
            if(this == &temp){
                return true;
            }
            if(length!=temp.length){
                return false;
            }
            return compare(root,temp.root);
       }
       void remove(T value){
        
       }

    private:
        void copy(Node<T> temp){
            if(temp!=nullptr){
                add(temp->value);
                copy(temp->right);
                copy(temp->left);
            }
        }

        bool compare(Node<T> temp1, Node<T> temp2){
            if((temp1!=nullptr && temp2==nullptr) || (temp1==nullptr && temp2!=nullptr)){
                return false;
            }
            if(temp1!=nullptr && temp2!=nullptr ){
                if(temp1->value!=temp2->value){
                    return false;
                }else{
                    return compare(temp1->left, temp2->left) && compare(temp1->right, temp2->right);
                }
            }
            return true; 
        }

        void addRec(Node<T> temp, T value){
            if(is_empty()){
                root = new Node<T>(value);
                length++;
            }else if(value<=temp->value){
                if(temp->left!=nullptr){
                    addRec(temp->left, value);
                }else{
                    temp->left = new Node<T>(value);
                    temp->left->parent=temp;
                    length++;
                }
            }else if(value > temp->value){
                if(temp->right!=nullptr){
                    addRec(temp->right, value);
                }else{
                    temp->right = new Node<T>(value);
                    temp->right->parent=temp;
                    length++;
                }
            }
        }
        void printRec(Node<T>* temp){
            if(temp!=nullptr){
                printRec(temp->left);
                cout<<temp->value<<" ";
                printRec(temp->right);
            }
        }

        bool findRec(Node<T>* temp, T value){
            if(temp!=nullptr){
                if(temp->value==value){
                    return true;
                }else{
                     if(temp->left!=nullptr){
                       return findRec(temp->left,value);
                    }   
                    if(temp->right!=nullptr){
                       return findRec(temp->right,value);
                    }
                }
            }
            return false;
        }

        void DestRec(Node<T>* temp){
            if(temp!=nullptr){
                if(temp->left!=nullptr){
                    DestRec(temp->left);
                }
                if(temp->right!=nullptr){
                    DestRec(temp->right);
                }
                delete temp;
            }    
        }
};
int main(){
    BinarySearchTree BST;
    BST.add(500);
    BST.add(321);
    BST.add(11);
    BST.add(456);
    BST.add(12);
    BST.add(65);
    BST.add(200);
    BST.print();
    cout<<endl;
    cout<<BST.find(65);
    cout<<endl;
    cout<<BST.find(-3);


    cout<<endl;
    return 0;
}