#include <iostream>
#include "AVL.h"
#include "BinaryTree.h"
#include <chrono>

int main(){
    AVL<int, std::string> avl_test;
    BinaryTree<int> bt_test;
    //Testing insertion and Destructor call
    //for (int i = 0; i<20; i++){
    //    int num = rand()%1000 + i;
    //    avl_test.insert(num, std::to_string(num));
    //    bt_test.insert(num);
    //}

    avl_test.insert(37, "thirty-seven");
    avl_test.insert(21, "twenty-one");
    avl_test.insert(51, "fifty-one");
    avl_test.insert(63, "sixty-three");
    avl_test.insert(42, "forty-two");
    avl_test.insert(29, "twenty-nine");
    avl_test.insert(12, "twelve");
    avl_test.insert(40, "twelve");
    //avl_test.insert(17, "seven-teen");
    //avl_test.insert(2, "two");
    //avl_test.printInOrder();
    //avl_test.insert(60, "sixty");
    //avl_test.insert(69, "sixty-nine");
    //avl_test.remove(29);
    //avl_test.insert(72, "seventy-two");
    //avl_test.remove(42);
    //avl_test.remove(21);
    //avl_test.insert(13, "thirteen");
    //avl_test.insert(25, "twenty-five");
    //avl_test.insert(20, "twenty");
    //avl_test.remove(20);
    //avl_test.remove(25);
    //avl_test.remove(29);
    //avl_test.remove(51);
    avl_test.printInOrder();
    avl_test.remove(37);


    avl_test.printInOrder();

    return 0;
}
