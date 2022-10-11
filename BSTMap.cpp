#include<iostream>
using namespace std;

class Rectangle{
    public:
    int width;
    int length;
    int area;
    int perimeter;
    Rectangle(){}
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
    public:
    virtual int hamematel(T a, T b){
        return 0;
    }
};

class SortByArea : public Comparator<Rectangle>{
    public:
    int hamematel(Rectangle a, Rectangle b){
        if(a.area > b.area){
            return 1;
        }else if(a.area < b.area){
            return -1;
        }
        return 0;
    }
};

class SortByPerimeter : public Comparator<Rectangle>{
    public:
    int hamematel(Rectangle a, Rectangle b){
        if(a.perimeter > b.perimeter){
            return 1;
        }else if(a.perimeter < b.perimeter){
            return -1;
        }
        return 0;
    }
};

class SortByWidth : public Comparator<Rectangle>{
    public:
    int hamematel(Rectangle a, Rectangle b){
        if(a.width > b.width){
            return 1;
        }else if(a.width < b.width){
            return -1;
        }
        return 0;
    }
};
class SortByLength : public Comparator<Rectangle>{
    public:
    int hamematel(Rectangle a, Rectangle b){
        if(a.length > b.length){
            return 1;
        }else if(a.length < b.length){
            return -1;
        }
        return 0;
    }
};


template <class Key, class Value>
class Node{
    public:
    Value value;
    Key key;
    Node* left;
    Node* right;
    Node* parent;
    Node(Key k, Value v){
        this->value = v;
        this->key = k;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
};

template <class K, class V>
class Map{
private:
    Node<K,V>* root = nullptr;
    int length = 0;
    Comparator<K>* comparator;
public:
        Map(Comparator<K>* p){
                this->comparator = p;
        }

        Map(const Map& BST){
            copy(BST.root);
        }

        bool is_empty(){
           return root==nullptr;
        }

        void add(K key,V value){
            addRec(root, value,key);
        }

        void print(){
            printRec(root);
        }

        ~Map(){
            DestRec(root);
        }

        bool find(K key){
            return findRec(root, key);
         }

        Node<K,V>* find_ptr(K key){
            return find_ptr(root,key);
        } 

        Map& operator=(const Map& temp){
            if(comparator->hamematel(this,&temp)==0){
                return* this;
            }
            if(!is_empty()){
                DestRec(root);
            }
            root = nullptr;
            copy(temp.root);
            return* this;
       }

       bool operator==(Map& temp){
            if(comparator->hamematel(this,&temp)==0){
                return true;
            }
            if(length!=temp.length){
                return false;
            }
            return compare(root,temp.root);
       }

       Node<K,V>* min(Node<K,V>* temp){
            auto t = temp;
            while(temp->left!=nullptr){
                t = temp->left;
                temp = temp->left;
            }
            return t;
       }

       bool remove(K key){
            bool flag = false;
            auto temp = find_ptr(key);
            //Node does not exist
            if(temp==nullptr){
                return false;
            }
            //No leafes
            if(temp->right==nullptr && temp->left==nullptr){
                auto t = temp->parent;
                if(comparator->hamematel(t->key,temp->key)==1){
                    flag = true;
                }
                delete temp;
                if(flag){
                    t->left=nullptr;
                }else{
                    t->right=nullptr;
                }
                --length;
                return true;
            }//only one leaf
            else if(temp->left==nullptr && temp->right!=nullptr){
                temp->key = temp->right->key;
                temp->value = temp->right->value;
                auto t = temp;
                delete temp->right;
                t->right=nullptr;
                --length;
                return true;
            }else if(temp->right==nullptr && temp->left!=nullptr){
                temp->key = temp->left->key;
                temp->value = temp->left->value;
                auto t = temp;
                delete temp->left;
                t->left=nullptr;
                --length;
                return true;
            }//2 leafs
            else{ 
                if(temp->right->left!=nullptr){
                    auto res = min(temp->right);
                    temp->key = res->key;
                    temp->value = res->value;
                    if(res->right == nullptr){
                        auto t = res->parent;
                        delete res;
                        t->left = nullptr;
                        --length;
                        return true;
                    }else{
                        auto t = res->parent;
                        t->left = res->right;
                        delete res;
                        --length;
                        return true;
                    }
                }else{
                    temp->key = temp->right->key;
                    temp->value = temp->right->value;
                    auto t = temp->right;
                    if(temp->right->right!=nullptr){
                        temp->right = temp->right->right;
                        delete t;
                        t = nullptr;
                        --length;
                        return true;
                    }else{
                        delete temp->right;
                        temp->right = nullptr;
                        --length;
                        return true;
                    }
                }
            }
            return false;
       }

private:
        void copy(Node<K,V>* temp){
            if(temp!=nullptr){
                add(temp->key,temp->value);
                copy(temp->right);
                copy(temp->left);
            }
        }

        bool compare(Node<K,V>* temp1, Node<K,V>* temp2){
            if((temp1!=nullptr && temp2==nullptr) || (temp1==nullptr && temp2!=nullptr)){
                return false;
            }
            if(temp1!=nullptr && temp2!=nullptr ){
                if(temp1->value!=temp2->value && temp1->key!=temp2->key){
                    return false;
                }else{
                    return compare(temp1->left, temp2->left) && compare(temp1->right, temp2->right);
                }
            }
            return true; 
        }

        void addRec(Node<K,V>* temp, V value, K key){
            if(is_empty()){
                if(!find(key)){
                    root = new Node<K,V>(key,value);
                    length++;
                }
            }else if((comparator->hamematel(key, temp->key))==-1){
                if(temp->left!=nullptr){
                    addRec(temp->left, value,key);
                }else{
                    if(!find(key)){
                        temp->left = new Node<K,V>(key,value);
                        temp->left->parent=temp;
                        length++;
                    }
                }
            }else if((comparator->hamematel(key, temp->key))==1){
                if(temp->right!=nullptr){
                    addRec(temp->right, value,key);
                }else{
                    if(!find(key)){
                        temp->right = new Node<K,V>(key,value);
                        temp->right->parent=temp;
                        length++;
                    }
                }
            }
        }
        
        void printRec(Node<K,V>* temp){
            if(temp!=nullptr){
                printRec(temp->left);
                cout<<temp->key<<":";
                cout<<temp->value<<endl;
                printRec(temp->right);
            }
        }

        bool findRec(Node<K,V>* temp, K key){
            if(temp!=nullptr){
                if(comparator->hamematel(temp->key,key)==0){
                    return true;
                }else{
                     if(temp->left!=nullptr){
                       return findRec(temp->left,key);
                    }   
                    if(temp->right!=nullptr){
                       return findRec(temp->right,key);
                    }
                }
            }
            return false;
        }

        Node<K,V>* find_ptr(Node<K,V>* temp, K key){
            if(temp!=nullptr){
                if(comparator->hamematel(temp->key,key)==0){
                    return temp;
                }else{
                     if(temp->left!=nullptr){
                       return find_ptr(temp->left,key);
                    }   
                    if(temp->right!=nullptr){
                       return find_ptr(temp->right,key);
                    }
                }
            }
            return nullptr;
        }

        void DestRec(Node<K,V>* temp){
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
    SortByArea SA;
    Map<Rectangle,string> BST(&SA);
    BST.add(Rectangle(20,30),"one");
    BST.add(Rectangle(10,30),"Two");
    BST.add(Rectangle(10,15),"Three");
    BST.add(Rectangle(12,5),"Four");
    BST.add(Rectangle(9,1),"Five");
    BST.print();

    cout<<endl;
    return 0;
}