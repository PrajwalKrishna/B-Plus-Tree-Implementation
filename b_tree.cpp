#include<iostream>
// #include <algorithm>

// template <typename T, class Compare = std::less<T>>
class BTree {
public:
    BTree(){
        root = NULL;
    }
    void insert(int key){
        root = insert(root,key).first;
    }
    int count(int key){
        return count(root, key);
    }
    bool find(int key){
        return count(root,key);
    }
    void traverse(){
         traverse(root,0);
    }
private:
    // Currently fixing the node size intend to change it later
    static const int node_size = 4;
    struct Element {
        Element(){
            count = 0;
        }
        int value;
        uint count;
    };
    struct Node {
        Node(){
            // Initialize node_size+1 pointers to null
            for(int i = 0;i <= node_size+2;i++)
                pointers[i] = NULL;
            filled = 0;
            // Declare every new node as leaf
            isLeaf = true;
        };
        // To store keys
        int keys[node_size+1];
        int count[node_size+1];
        // To store pointers to children
        Node * pointers[node_size+2];
        // count of currently used slots in node
        int filled;
        // To see if it a leaf node or not
        bool isLeaf;
    };
    Node * root;
    void traverse(const Node * root,int depth){
        std::cout<<"Root:"<<depth<<"->";
        for(int i=0;i<root->filled;i++)
            std::cout<<root->keys[i]<<' ';
        std::cout<<'\n';
        for(int i=0;i<=root->filled;i++)
            if(root->pointers[i])
                traverse(root->pointers[i],depth+1);
    }
    Node * splitNode(Node *root,int key){
        Node * left = new Node;
        Node * right = new Node;
        int mid = node_size/2;

        left->filled = mid;
        right->filled = node_size - mid;

        for(int i=0;i<mid;i++){
            left->keys[i] = root->keys[i];
            left->pointers[i] = root->pointers[i];
        }
        left->pointers[left->filled] = root->pointers[mid];

        for(int i=mid+1;i<=node_size;i++){
            right->keys[i-mid-1] = root->keys[i];
                right->pointers[i-mid-1] = root->pointers[i];
        }
        right->pointers[right->filled] = root->pointers[node_size+1];

        if(root->isLeaf)
            root->isLeaf = false;
        else
            left->isLeaf = right->isLeaf = false;
        root->keys[0] = root->keys[mid];
        root->filled = 1;
        root->pointers[0] = left;
        root->pointers[1] = right;
        for(int i=2;i<=node_size+1;i++)
            root->pointers[i] = 0;
        return root;
    }
    std::pair<Node *,bool> insert(Node * root, int key){
        if(root == NULL)
        {
            root = new Node;
            root->keys[root->filled++] = key;
            return {root,false};
        }
        if(root->isLeaf)
        {
            int index = 0;
            for(;index<root->filled;index++)
                if(root->keys[index] > key)
                    break;
            for(int i=root->filled;i>index;i--)
                root->keys[i]=root->keys[i-1];
            root->keys[index] = key;
            root->filled++;
            if(root->filled <= node_size)
                return {root,false};
            // Else split node
            root = splitNode(root,key);
            return {root,true};
        }
        int index = 0;
        for(;index<root->filled;index++)
            if(root->keys[index] > key)
                break;

        std::pair<Node*,bool> temp;
        temp = insert(root->pointers[index],key);
        if(temp.second){
            int index = 0;
            for(;index<root->filled;index++)
                if(root->keys[index] > temp.first->keys[0])
                    break;
            for(int i=root->filled;i>index;i--){
                root->keys[i]=root->keys[i-1];
                root->pointers[i+1]=root->pointers[i];
            }
            root->keys[index] = (temp.first)->keys[0];
            root->pointers[index] = temp.first->pointers[0];
            root->pointers[index+1] = temp.first->pointers[1];
            delete temp.first;
            root->filled++;

            if(root->filled <= node_size)
                return {root,false};
            // Else split
            root = splitNode(root,key);
            return {root,true};
        }
        else
            root->pointers[index] = temp.first;
        return {root,false};
    }
    int count(Node * root, int key){
        std::cout<<"Hi "<<key<<'\n';
    }
};
int main()
{
    BTree multiset;
    std::cout<<"Number of elements:\n";
    int n,t;
    std::cin>>n;
    for(int i=0;i<n;i++)
    {
        std::cin>>t;
        multiset.insert(t);
        multiset.traverse();
    }
    return 0;
}
