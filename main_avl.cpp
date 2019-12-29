#include <iostream>
#include "AVL.h"
#include "BinaryTree.h"
#include <chrono>

int main(){
    AVL<int, std::string> avl_test;
    BinaryTree<int> bt_test;
    //Testing insertion and Destructor call
    for (int i = 0; i<20; i++){
        int num = rand()%1000 + i;
        avl_test.insert(num, std::to_string(num));
        bt_test.insert(num);
    }

    //avl_test.insert(37, "thirty-seven");
    //avl_test.insert(51, "fifty-one");
    //avl_test.insert(16, "sixteen");
    //avl_test.insert(4, "four");
    //avl_test.insert(1, "one");
    //avl_test.insert(7, "seven");
    //avl_test.printInOrder();
    //avl_test.insert(60, "sixty");
    //avl_test.insert(69, "sixty-nine");
    //avl_test.insert(55, "sixty-nine");
    avl_test.printInOrder();
    std::cout<<bt_test;

    return 0;
}
