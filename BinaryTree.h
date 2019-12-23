#pragma once

#include <iostream>

template <typename T>
class BinaryTree{
public:
    //Constructor to initialize the headpointer of the binary tree to null
    BinaryTree(): head_(nullptr) {}

    //Destructor
    ~BinaryTree() {
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

    //Function to delete the whole Binary Tree. Used in destructor
    void deleteTree(TreeNode*& currNode){
        if (currNode->left!=nullptr){
            deleteTree(currNode->left);
        }
        if (currNode->right!=nullptr){
            deleteTree(currNode->right);
        }
        delete currNode;
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
    //This is not a generic swap function
    //This specifically swaps the iopNode with the currNode
    //Don't try with other situations. Those have not been incorportated
    void swap_(TreeNode *& iopNode, TreeNode *& currNode);

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
    currNode = new TreeNode(data);
}

template <typename T>
void BinaryTree<T>::remove(const T& data) {
    TreeNode *& currNode = find_(data, head_);

    if (currNode==nullptr) throw std::runtime_error(std::string("Data not found in Tree. Can't remove!"));
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
    swap_(iopNode, currNode);
    iopNode = nullptr;
    delete iopNode;
}

template <typename T>
void BinaryTree<T>::swap_(TreeNode *& iopNode, TreeNode *& currNode){
    //T data = currNode->data;
    //currNode->data = iopNode->data;
    //iopNode->data = data;
    //std::cout<<"iopNode:\n";
    //displayNode_(iopNode);
    //std::cout<<"currNode:\n";
    //displayNode_(currNode);

    TreeNode* original_iopNode  = iopNode;
    TreeNode* original_currNode = currNode;

    //std::cout<<"original_iopNode:\n";
    //displayNode_(original_iopNode);
    //std::cout<<"original_currNode:\n";
    //displayNode_(original_currNode);
    iopNode  = original_currNode;
    currNode = original_iopNode;

    currNode->left  = original_currNode->left;
    currNode->right = original_currNode->right;

    iopNode->left  = nullptr;
    iopNode->right = nullptr;


    //std::cout<<"New iopNode:\n";
    //displayNode_(iopNode);
    //std::cout<<"New currNode:\n";
    //displayNode_(currNode);
}

template <typename T>
typename BinaryTree<T>::TreeNode*& BinaryTree<T>::iop_(TreeNode *& currNode){
    if((currNode->left==nullptr) && (currNode->right==nullptr)){
        //std::cout<<"Node Data: "<<currNode->data<<'\n';
        return currNode;
    }
    return iop_(currNode->right);
}
