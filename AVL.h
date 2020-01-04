#pragma once

#include <stdexcept>
#include <iostream>
#include <queue>
#include <stack>

//==============================================================================
//AVL Tree: https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
//==============================================================================

//Key,value based AVL
template <typename K, typename D>
class AVL{
private:
    class TreeNode{
    public:
        K key;
        D data;
        TreeNode* left;
        TreeNode* right;
        int height;

        //Constructor
        TreeNode(): left(nullptr), right(nullptr), height(0) {};

        //Argument based Constructor
        TreeNode(const K& key_arg, const D& data_arg): key(key_arg), data(data_arg), left(nullptr), right(nullptr), height(0) {};
    };

public:
    //Constructor
    AVL(): head_(nullptr), node_count_(0) {};

    //clear_tree:Delete all the Nodes from the tree
    void clear_avl();

    //Destructor
    ~AVL(){
        std::cout<<"AVL Destructor called\n";
        delete_avl_(head_);
    };

    //Insert a key,data into AVL tree
    void insert(const K& key_arg, const D& data_arg);

    //Remove a Node with "key_arg" as key
    void remove(const K& key_arg);

    //print In order
    void printInOrder() const {
        std::cout<<"Printing In Order:\n";
        printInOrder_(head_);
    }

private:
    TreeNode* head_;

    int node_count_;

    //==========================================================================
    //                        Function Declarations
    //==========================================================================
    //function to display the Node
    void displayNode_(const TreeNode* Node) const;

    void printInOrder_(const TreeNode* currNode) const;

    //function to delete the AVL subtree/tree from given node
    void delete_avl_(TreeNode*& Node);

    //find_() function takes two arguments:-
    //Arg 1: a key argument passed by constant reference
    //Arg 2: a pointer to a TreeNode passed by reference
    //Return type: Returns a pointer to a TreeNode as reference. Hence, the
    //returned pointer can be used to modify the TreeNode
    //"const" at the end signifies that it doesn't modify the class instance
    TreeNode*& find_(const K& key_arg, TreeNode*& Node) const;

    //remove_() function takes one argument:
    //Arg 1: a pointer to TreeNode passed by reference
    //Return type: void
    //This function may need to call _iopRemove function for certain cases
    void remove_(TreeNode*& Node);
    void find_and_remove_(const K& key, TreeNode *& Node);
    void iopRemove_(TreeNode*& targetNode);
    void iopRemove_(TreeNode*& targetNode, TreeNode*& iopAncestor);
    TreeNode*& swap_(TreeNode *& Node1, TreeNode *& Node2);
    //==========================================================================
    //                Functions for insertion
    //==========================================================================
    //Insert function
    void insert_(const K& key_arg, const D& data_arg, TreeNode*& Node);

    //Balance a subtree if it has a balance factor >=2 or <=-2 at the Node
    void ensure_balance_(TreeNode*& Node);

    //update_height_() updates the "height" of each of the node in the AVL
    void update_height_(TreeNode*& Node);

    //get_height_() reutrns the height of the sub-tree/tree from given node
    int get_height_(TreeNode*& Node) const;

    //Function to obtain balance factor at a particular node
    int get_balance_factor_(TreeNode*& Node);

    //==========================================================================
    //Rotation required for balancing of AVL
    void rotateLeft_(TreeNode*& Node);
    void rotateRight_(TreeNode*& Node);
    void rotateRightLeft_(TreeNode*& Node);
    void rotateLeftRight_(TreeNode*& Node);
    //==========================================================================

};

//==============================================================================
//                        Public Function Implementations
//==============================================================================
template <typename K, typename D>
void AVL<K,D>::insert(const K& key_arg, const D& data_arg) {
    //Find location to insert the new node
    //std::cout<<"===============================================================\n";
    insert_(key_arg, data_arg, head_);
    //std::cout<<"===============================================================\n\n";
}

template <typename K, typename D>
void AVL<K, D>::remove(const K& key) {
    find_and_remove_(key, head_);
}

template <typename K, typename D>
void AVL<K, D>::find_and_remove_(const K& key, TreeNode *& Node) {
    if (Node == nullptr){
        return;
    }

    if (key == Node->key){
        remove_(Node);
        return;
    }
    else if (key < Node->key) {
        find_and_remove_(key, Node->left);
        ensure_balance_(Node);
        return;
    }
    else if (key > Node->key) {
        find_and_remove_(key, Node->right);
        ensure_balance_(Node);
        return;
    }
}

template <typename K, typename D>
void AVL<K,D>::remove_(TreeNode*& currNode) {
    //Case 1
    //Node being removed has no childs
    if ((currNode->left == nullptr) && (currNode->right == nullptr)){
        delete currNode;
        currNode = nullptr;
        return;
    }
    //Case 2
    //Node being removed has one left child
    else if ((currNode->left != nullptr) && (currNode->right == nullptr)){
        TreeNode *& tempNode = currNode->left;
        delete currNode;
        currNode = tempNode;
        return;
    }
    //Case 3
    //Node being removed has one right child
    else if ((currNode->left == nullptr) && (currNode->right != nullptr)){
        TreeNode *& tempNode = currNode->right;
        delete currNode;
        currNode = tempNode;
        return;
    }
    else {
        //throw(std::runtime_error(std::string("iopRemove not supported yet")));
        iopRemove_(currNode);
    }
}

template <typename K, typename D>
void AVL<K, D>::iopRemove_(TreeNode*& targetNode) {
    iopRemove_(targetNode, targetNode->left);
    ensure_balance_(targetNode);
}

template <typename K, typename D>
void AVL<K, D>::iopRemove_(TreeNode*& targetNode, TreeNode*& iopAncestor) {
    if (iopAncestor->right != nullptr) {
        iopRemove_(targetNode, iopAncestor->right);
        ensure_balance_(iopAncestor);
     }
     else {
        TreeNode *& movedTarget = swap_(targetNode, iopAncestor);
        remove_(movedTarget);
    }
}

template <typename K, typename D>
typename AVL<K,D>::TreeNode*& AVL<K,D>::swap_(TreeNode *& Node1, TreeNode *& Node2){
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

        //We are returning the new postion of Node1 by reference
        return Node2;
    }
}

//==============================================================================
//                        Private Function Implementations
//==============================================================================
template <typename K, typename D>
void AVL<K,D>::displayNode_(const TreeNode* Node) const {
    std::cout<<"--------------------------------------\n";
    std::cout<<"Node Addr: "<<Node<<'\n';
    std::cout<<"Key: "<<Node->key<<" | Data: "<<Node->data<<" | Height: "<<Node->height<<'\n';
    std::cout<<"Left: "<<Node->left<<" | Right: "<<Node->right<<'\n';
    std::cout<<"--------------------------------------\n\n";
}

template <typename K, typename D>
void AVL<K, D>::printInOrder_(const TreeNode* currNode) const {
    if (currNode==nullptr){
        return;
    }

    printInOrder_(currNode->left);
    displayNode_(currNode);
    printInOrder_(currNode->right);
}

template <typename K, typename D>
void AVL<K,D>::delete_avl_(TreeNode*& Node){
    if (Node == nullptr){
        return;
    }
    if(Node->left != nullptr){
        delete_avl_(Node->left);
    }
    if(Node->right != nullptr){
        delete_avl_(Node->right);
    }
    //This means that Node has both its left and right pointers null
    //std::cout<<"Deleting Node\n";
    //displayNode_(Node);
    //delete Node;
    Node = nullptr;
}

template <typename K, typename D>
typename AVL<K,D>::TreeNode*& AVL<K,D>::find_(const K& key_arg, TreeNode*& Node) const {
    if (Node == nullptr) {
        return Node;
    }

    if (key_arg == Node->key){
        return Node;
    }

    if (key_arg < Node->key){
        return find_(key_arg, Node->left);
    }
    else{
        return find_(key_arg, Node->right);
    }
}

template <typename K, typename D>
void AVL<K,D>::insert_(const K& key_arg, const D& data_arg, TreeNode*& Node){

    if (Node == nullptr){
        Node = new TreeNode(key_arg, data_arg);
        //Debug
        //std::cout<<"Inserting new Node:"<<"\n";
        //std::cout<<"Key:"<<key_arg<<" Data: "<<data_arg<<"\n\n";
        return;
    }

    if (Node->key == key_arg){
        throw std::runtime_error(std::string("Key already present Cannot enter duplicate"));
    }

    if (key_arg < Node->key){
        insert_(key_arg, data_arg, Node->left);
        //ensure_balance_() make sure that the AVL is balanced. It needs to be
        //run from the current node location i.e. "Node". Because a new node has
        //been inserted to the left sub-tree of "Node" which can cause imbalance
        //to the subtree whose root is this "Node". No need to worry about the
        //other parts of the AVL
        ensure_balance_(Node);
    }
    else{
        insert_(key_arg, data_arg, Node->right);
        //Same logic as above
        ensure_balance_(Node);
    }
}

template <typename K, typename D>
void AVL<K, D>::ensure_balance_(TreeNode*& Node) {
    if (Node ==  nullptr){
        return;
    }

    //Before ensuring balance at the node we update the height of all the nodes
    //which are children. This makes it easy to use update_height_()
    //We can call ensure_balance_ without worrying about whether we need to explicitly
    //call update_height_ or not outside
    update_height_(Node);

    //A negative value means AVL is tilted towards left
    //A positive value means AVL is tilted towards right
    int balance_factor = get_balance_factor_(Node);
    //From theory we know that any subtree of an AVL cannot have balance factor
    //greater than 2 or less than -2. At every insertion we balance the tree.
    //So the range of values that balance factor can take are [-2, -1, 0, 1, 2]
    if ((balance_factor < -2) || (balance_factor > 2)){
        std::string msg("Error: Initial balance factor: ");
        msg += std::to_string(balance_factor);
        msg += "; Inital balance factor of greater than 2 or less than -2 not possible.";
        throw std::runtime_error(msg);
    }

    if (balance_factor == -2){
        //Debug
        std::cout<<"Balancing at Node:\n";
        displayNode_(Node);

        //Means the subtree is left tilted
        int left_subtree_balance_factor = get_balance_factor_(Node->left);
        if ((left_subtree_balance_factor == -1) || (left_subtree_balance_factor == 0)){
            rotateRight_(Node);
        }
        else if (left_subtree_balance_factor == 1) {
            rotateLeftRight_(Node);
        }
        else{
            // Error checking
            std::string msg("ERROR: left_subtree_balance_factor has unexpected value: ");
            msg += std::to_string(left_subtree_balance_factor);
            msg += " ; This should never happen here.";
            throw std::runtime_error(msg);
        }

        //Debug
        //std::cout<<"After Rotation:\n";
        //printInOrder_(head_);

        //After rebalancing we are updating the heights of the nodes again to
        //keep the height values correct
        update_height_(Node);
    }

    if (balance_factor == 2){
        //Debug
        std::cout<<"Balancing at Node:\n";
        displayNode_(Node);

        //Means the subtree is right tilted
        int right_subtree_balance_factor = get_balance_factor_(Node->right);
        if ((right_subtree_balance_factor == 1) || (right_subtree_balance_factor == 0)) {
            rotateLeft_(Node);
        }
        else if (right_subtree_balance_factor == -1) {
            rotateRightLeft_(Node);
        }
        else{
            // Error checking
            std::string msg("ERROR: right_subtree_balance_factor has unexpected value: ");
            msg += std::to_string(right_subtree_balance_factor);
            msg += " ; This should never happen here.";
            throw std::runtime_error(msg);
        }

        //Debug
        //std::cout<<"After Rotation:\n";
        //printInOrder_(head_);

        //After rebalancing we are updating the heights of the nodes again to
        //keep the height values correct
        update_height_(Node);
    }

    //Debug
    //std::cout<<"After Height Update:\n";
    //printInOrder_(head_);

    ////This should fix the balance factor upto this Node
    //balance_factor = get_balance_factor_(Node);
    //if ((balance_factor <= -2) || (balance_factor >= 2)){
    //    std::string msg("Error: New Balance factor: ");
    //    msg += std::to_string(balance_factor);
    //    msg += "; New balance factor >= 2 or <= -2 not possible.";
    //    throw std::runtime_error(msg);
    //}
}

template <typename K, typename D>
int AVL<K, D>::get_balance_factor_(TreeNode*& Node) {
    //This case should not be happening
    if (Node == nullptr){
        throw std::runtime_error(std::string("get_balance_factor_() called on nullptr"));
    }
    return get_height_(Node->right) - get_height_(Node->left);
}

template <typename K, typename D>
void AVL<K,D>::update_height_(TreeNode*& Node){
    if ((Node->left == nullptr) && (Node->right == nullptr)) {
        Node->height = 0;
        return;
    }
    //Debug
    //std::cout<<"Updating height:\n";
    //displayNode_(Node);

    if (Node->left != nullptr){
        update_height_(Node->left);
    }
    if (Node->right != nullptr){
        update_height_(Node->right);
    }
    if ((Node->left != nullptr) && (Node->right != nullptr)){
        Node->height = 1 + std::max(Node->left->height, Node->right->height);
    }
    else if (Node->left == nullptr) {
        Node->height = 1 + Node->right->height;
    }
    else if (Node->right == nullptr) {
        Node->height = 1 + Node->left->height;
    }

}

template <typename K, typename D>
int AVL<K,D>::get_height_(TreeNode*& Node) const {
    if (Node == nullptr){
        return -1;
    }
    else {
        return Node->height;
    }
}

template <typename K, typename D>
void AVL<K,D>::rotateRight_(TreeNode*& Node) {
    if (Node == nullptr) {
        throw std::runtime_error(std::string("Error: rotateRight"));
    }

    //Debug
    // std::cout<<"Performing Right rotation at Node:\n";
    // displayNode_(Node);

    TreeNode* left_Node = Node->left;
    Node->left = left_Node->right;
    left_Node->right = Node;
    Node = left_Node;
}

template <typename K, typename D>
void AVL<K,D>::rotateLeft_(TreeNode*& Node) {
    if (Node == nullptr) {
        throw std::runtime_error(std::string("Error: rotateLeft"));
    }

    //Debug
    // std::cout<<"Performing Left rotation at Node:\n";
    // displayNode_(Node);

    TreeNode* right_Node = Node->right;
    Node->right = right_Node->left;
    right_Node->left = Node;
    Node = right_Node;
}

template <typename K, typename D>
void AVL<K,D>::rotateRightLeft_(TreeNode*& Node) {
    if (Node == nullptr) {
        throw std::runtime_error(std::string("Error: rotateRightLeft"));
    }

    //Debug
    // std::cout<<"Performing RightLeft rotation at Node:\n";
    // displayNode_(Node);

    rotateRight_(Node->right);
    rotateLeft_(Node);
}

template <typename K, typename D>
void AVL<K,D>::rotateLeftRight_(TreeNode*& Node) {
    if (Node == nullptr) {
        throw std::runtime_error(std::string("Error: rotateLeftRight; Called on nullptr"));
    }

    //Debug
    // std::cout<<"Performing LeftRight rotation at Node:\n";
    // displayNode_(Node);

    rotateLeft_(Node->left);
    rotateRight_(Node);
}
