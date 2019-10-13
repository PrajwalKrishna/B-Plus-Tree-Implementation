#include<iostream>
// #include <algorithm>

// template <typename T, class Compare = std::less<T>>
class BPlusTree {
public:
    BPlusTree(){
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
    static const int node_size = 3;
    struct Node {
        Node(){
            // Initialize node_size+1 pointers to null
            for(int i = 0;i <= node_size+2;i++)
                pointers[i] = NULL;
            filled = 0;
            // Declare every new node as leaf
            isLeaf = true;
            next = NULL;
        };
        // To store keys
        int keys[node_size+1];
        // To store pointers to children
        Node * pointers[node_size+2];
        // count of currently used slots in node
        int filled;
        // To see if it a leaf node or not
        bool isLeaf;
        Node * next;
    };
    Node * root;
    void traverse(const Node * root,int depth){
        std::cout<<"Root:"<<depth<<"->";
        for(int i=0;i<root->filled;i++)
            std::cout<<root->keys[i]<<' ';
        std::cout<<'\n';
        for(int i=0;i<=root->filled;i++)
            if(root->pointers[i]!=NULL)
                traverse(root->pointers[i],depth+1);
    }
    Node * splitNode(Node *root,int key){
        Node * new_root = new Node;
        Node * right = new Node;
        int mid = node_size/2;

        right->filled = node_size - mid;
        for(int i=mid+1;i<=node_size;i++){
            right->keys[i-mid-1] = root->keys[i];
            right->pointers[i-mid-1] = root->pointers[i];
        }
        right->pointers[right->filled] = root->pointers[node_size+1];
        right->isLeaf = root->isLeaf;

        new_root->isLeaf = false;
        new_root->keys[0] = root->keys[mid];
        new_root->filled = 1;
        new_root->pointers[0] = root;
        new_root->pointers[1] = right;

        for(int i=mid+1;i<=node_size+1;i++)
            root->pointers[i] = NULL;
        if(root->isLeaf){
            root->filled = mid+1;
            // next pointer
            right->next = root->next;
            root->next = right;
        }
        else
            root->filled = mid;

        return new_root;
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
    BPlusTree multiset;
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
