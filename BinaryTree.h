#pragma once

#include <iostream>
#include <math.h>
#include <queue>

//Class for Binary Search Tree
template <typename T>
class BinaryTree{
public:
    //Constructor to initialize the headpointer of the binary tree to null
    BinaryTree(): head_(nullptr), node_count_(0) {}

    //Destructor
    ~BinaryTree() {
        std::cout<<"BinaryTree Destructor called\n";
        deleteTree(head_);
    };

    //print In order
    std::ostream& printInOrder(std::ostream & os) const {
        os<<"[ ";
        printInOrder_(os, head_);
        os<<"]\n";
        return os;
    }

    //Function to check if the data exists or not
    bool check(const T& data) const;

    //Insert function
    void insert(const T& data);

    //Remove function
    void remove(const T& data);

    //Get the Height of the binary tree
    int getheight(){
        return getheight_(head_);
    };

    //Check if binary tree is perfect or not
    bool isPerfect() const;
    //Check if binary tree is Full or not
    bool isFull() const;
    //Check if binary tree is Complete or not
    bool isComplete() const;

    //Check whether binary tree empty or not
    bool empty() const {
        return !head_;
    }

private:
    class TreeNode{
    public:
        T data;
        TreeNode* left;
        TreeNode* right;

        //Default constructor for TreeNode
        TreeNode(): left(nullptr), right(nullptr) {};

        //Argument based constructor for TreeNode
        TreeNode(const T& data): data(data), left(nullptr), right(nullptr) {}
    };

    TreeNode* head_;    //Pointer to head of the binary tree

    int node_count_;

    //==========================================================================
    //                            Functions
    //==========================================================================

    //Function to delete the whole Binary Tree. Used in destructor
    void deleteTree(TreeNode*& currNode){
        if (currNode==nullptr) {
            return;
        }
        if (currNode->left!=nullptr){
            deleteTree(currNode->left);
        }
        if (currNode->right!=nullptr){
            deleteTree(currNode->right);
        }
        //std::cout<<"Deleting Node:\n";
        //displayNode_(currNode);
        delete currNode;
        currNode = nullptr;
    }

    //Function to check if a data exists in the BinaryTree or not
    bool check_(const T& data, TreeNode* currNode) const;

    //This function returns a reference to a pointer to a TreeNode
    //Since this doesn't return a constant reference we can use this to
    //make changes the TreeNode, pointed to, by the pointer.
    //Pointer to currNode is passed by reference because we are returning currNode
    //itself and then modifying it in the insert function. Cannot pass by value
    //i.e. TreeNode* currNode will give segmentation fault
    TreeNode*& find_(const T& data, TreeNode*& currNode) const;

    //Here I have two insert_ functions.
    //One takes a reference of the pointer to a TreeNode - This one is easy on the eye
    //Other takes a pointer to a pointer to a TreeNode - This one is slightly more complex
    //Remeber reference to a pointer and a pointer to a pointer are pretty much doing the
    //same job
    void insert_(const T& data, TreeNode*& currNode);
    //void insert_(const T& data, TreeNode** currNode);

    TreeNode*& iop_(TreeNode *& currNode);

    //Swap function to swap nodes
    //Returns a pointer to TreeNode pointing to the new moved Node1
    //For some cases Node1 and Node2 are not usable, i.e. they form a loop
    //For example when Node2 is left child of Node1. In such case avoid
    //using Node1 and Node2 and instead use the TreeNode pointer returned
    //by this function
    TreeNode*& swap_(TreeNode *& Node1, TreeNode *& Node2);

    int getheight_(const TreeNode* currNode) const;

    //Helper function for remove()
    void remove_(TreeNode *& currNode);

    //Recursion based helper function required for isComplete()
    bool isComplete_(const TreeNode* Node, int index) const;

    //print the binary tree in order
    void printInOrder_(std::ostream & os, const TreeNode* currNode) const;

    void displayNode_(const TreeNode* currNode){
        std::cout<<"-------------------------------------------------------\n";
        std::cout<<"Address: "<<currNode<<" Data: "<<currNode->data<<'\n';
        std::cout<<"Address->left: "<<currNode->left<<'\n';
        std::cout<<"Address->right: "<<currNode->right<<'\n';
        std::cout<<"-------------------------------------------------------\n";
    }
};


//std::cout << operator overload for LinkedList
template <typename T>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T> & bt){
    return bt.printInOrder(os);
}

template <typename T>
void BinaryTree<T>::printInOrder_(std::ostream& os, const TreeNode* currNode) const {
    if (currNode==nullptr){
        return;
    }

    printInOrder_(os, currNode->left);
    os<<currNode->data<<" ";
    printInOrder_(os, currNode->right);
}

template <typename T>
bool BinaryTree<T>::check_(const T& data, TreeNode* currNode) const {
    if (currNode==nullptr){
        return false;
    }

    if (currNode->data==data){
        //std::cout<<"-------------------------------------------------------\n";
        //std::cout<<"Address: "<<currNode<<" Data: "<<currNode->data<<'\n';
        //std::cout<<"Address->left: "<<currNode->left<<'\n';
        //std::cout<<"Address->right: "<<currNode->right<<'\n';
        //std::cout<<"-------------------------------------------------------\n";
        return true;
    }

    if (data < currNode->data){
        return check_(data, currNode->left);
    }
    else{
        return check_(data, currNode->right);
    }
}

template <typename T>
void BinaryTree<T>::insert_(const T& data, TreeNode*& currNode) {
    if(data < currNode->data){
        if(currNode->left==nullptr){
            currNode->left = new TreeNode(data);
        }
        else{
            insert_(data, currNode->left);
        }
    }
    else{
        if(currNode->right==nullptr){
            currNode->right = new TreeNode(data);
        }
        else{
            insert_(data, currNode->right);
        }
    }
}

// template <typename T>
// void BinaryTree<T>::insert_(const T& data, TreeNode** currNode) {
//     if(data < (*currNode)->data){
//         if((*currNode)->left==nullptr){
//             (*currNode)->left = new TreeNode(data);
//         }
//         else{
//             insert_(data, &((*currNode)->left));
//         }
//     }
//     else{
//         if((*currNode)->right==nullptr){
//             (*currNode)->right = new TreeNode(data);
//         }
//         else{
//             insert_(data, &((*currNode)->right));
//         }
//     }
// }

template <typename T>
bool BinaryTree<T>::check(const T& data) const {
    if (head_==nullptr){
        return false;
    }
    return check_(data, head_);

}

template <typename T>
typename BinaryTree<T>::TreeNode*& BinaryTree<T>::find_(const T& data, TreeNode *& currNode) const {
    if (currNode==nullptr){
        return currNode;
    }

    if (currNode->data==data){
        return currNode;
    }

    if (data < currNode->data){
        return find_(data, currNode->left);
    }
    else{
        return find_(data, currNode->right);
    }
}

template <typename T>
void BinaryTree<T>::insert(const T& data){
    //Using find_ to obtain a reference to the pointer to TreeNode where we will insert
    //For the case of insert, find_ will return a null pointer. If it didn't, then it means
    //that the data was already present which is a runtime error
    TreeNode *& currNode = find_(data, head_);
    if (currNode!=nullptr)  throw std::runtime_error(std::string("This element already exists. Cannot insert duplicates!"));
    node_count_++;
    currNode = new TreeNode(data);
}

template <typename T>
void BinaryTree<T>::remove(const T& data) {
    TreeNode *& currNode = find_(data, head_);
    if (currNode==nullptr) throw std::runtime_error(std::string("Data not found in Tree. Can't remove!"));
    node_count_--;
    return remove_(currNode);
}

template <typename T>
void BinaryTree<T>::remove_(TreeNode*& currNode) {
    if ((currNode->left == nullptr) && (currNode->right == nullptr)){
        delete currNode;
        currNode = nullptr;
        return;
    }

    if ((currNode->left != nullptr) && (currNode->right == nullptr)){
        TreeNode *& tempNode = currNode->left;
        delete currNode;
        currNode = tempNode;
        return;
    }

    if ((currNode->left == nullptr) && (currNode->right != nullptr)){
        TreeNode *& tempNode = currNode->right;
        delete currNode;
        currNode = tempNode;
        return;
    }

    TreeNode *& iopNode = iop_(currNode->left);
    TreeNode *& movedNode = swap_(currNode, iopNode);
    remove_(movedNode);
}

template <typename T>
typename BinaryTree<T>::TreeNode*& BinaryTree<T>::swap_(TreeNode *& Node1, TreeNode *& Node2){
    TreeNode* original_Node1 = Node1;
    TreeNode* original_Node2 = Node2;

    if (Node1->left==Node2){

        std::swap(Node1->right, Node2->right);
        Node1->left = original_Node2->left;
        original_Node2->left = original_Node1;
        Node1 = original_Node2;

        //We cannot change Node2 here because it changes Node1->left as well
        //This will become a never ending loop
        //Hence, avoid using Node1 and Node2 and instead use the returned pointer
        return Node1->left;
    }
    else if (Node1->right==Node2){
        std::swap(Node1->left, Node2->left);
        Node1->right = original_Node2->right;
        original_Node2->right = original_Node1;
        Node1 = original_Node2;

        return Node1->right;
    }

    else if (Node2->left==Node1){
        std::swap(Node1->right, Node2->right);
        Node2->left = original_Node1->left;
        original_Node1->left = original_Node2;
        Node2 = original_Node1;

        return Node2->left;
    }
    else if (Node2->right==Node1){
        std::swap(Node1->left, Node2->left);
        Node2->right = original_Node1->right;
        original_Node1->right = original_Node2;
        Node2 = original_Node1;

        return Node2->right;
    }
    else{
        //std::cout<<"Original Node1:\n";
        //displayNode_(Node1);
        //std::cout<<"Original Node2:\n";
        //displayNode_(Node2);

        std::swap(Node1->left, Node2->left);
        std::swap(Node1->right, Node2->right);
        std::swap(Node1, Node2);

        //std::cout<<"New Node1:\n";
        //displayNode_(Node1);
        //std::cout<<"New Node2:\n";
        //displayNode_(Node2);

        return Node2;
    }
}

template <typename T>
typename BinaryTree<T>::TreeNode*& BinaryTree<T>::iop_(TreeNode *& currNode){
    if((currNode->left==nullptr) && (currNode->right==nullptr)){
        //std::cout<<"Node Data: "<<currNode->data<<'\n';
        return currNode;
    }
    if(currNode->right==nullptr){
        return currNode;
    }
    else{
        return iop_(currNode->right);
    }
}

template <typename T>
int BinaryTree<T>::getheight_(const TreeNode* currNode) const {
    if ((currNode->left==nullptr) && (currNode->right==nullptr)){
        return 0;
    }
    if ((currNode->left==nullptr) && (currNode->right!=nullptr)) {
        return 1 + getheight_(currNode->right);
    }
    if ((currNode->left!=nullptr) && (currNode->right==nullptr)) {
        return 1 + getheight_(currNode->left);
    }
    return 1 + std::max(getheight_(currNode->left), getheight_(currNode->right));
}

template <typename T>
bool BinaryTree<T>::isPerfect() const {
    int height = getheight_(head_);
    if ( node_count_ != (pow(2,height)-1)){
        return false;
    }
    return true;
}


//A Binary Tree is Full if every node has either 0 or 2 children.
//It is not necessary that all the leaf nodes be at the same level.
template <typename T>
bool BinaryTree<T>::isFull() const {
    if (head_==nullptr){
        return true;
    }
    std::queue<TreeNode*> nodes_to_check;
    nodes_to_check.push(head_);

    while(!nodes_to_check.empty()){
        TreeNode* currNode = nodes_to_check.front();
        nodes_to_check.pop();

        //If any node has a single child(left/right) then this binary tree
        //is not full. Hence, return false.
        if((currNode->left == nullptr && currNode->right != nullptr) ||
        (currNode->left != nullptr && currNode->right == nullptr)){
            return false;
        }

        //If the node has a left and right child node then push it into the
        //queue. It needs to be checked. We don't need to push nodes which don't
        //have any children because they are leaf nodes themselves.
        if (currNode->left != nullptr && currNode->right != nullptr){
            nodes_to_check.push(currNode->left);
            nodes_to_check.push(currNode->right);
        }
    }
    return true;

}

//A Binary Tree is complete if all the levels are completely filled except maybe
//the last level. The last level may or may not be completely filled. And if it
//is not completely filled then all the leaf nodes must be to the left.
template <typename T>
bool BinaryTree<T>::isComplete() const {
    return isComplete_(head_, 0);
}

template <typename T>
bool BinaryTree<T>::isComplete_(const TreeNode* Node, int index) const {
    if (Node == nullptr){
        return true;
    }

    if (index >= node_count_){
        return false;
    }

    return (isComplete_(Node->left, 2*index+1) && isComplete_(Node->right, 2*index+2));
}
