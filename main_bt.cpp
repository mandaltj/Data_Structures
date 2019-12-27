#include <iostream>
#include "BinaryTree.h"
#include <chrono>

int main(){
    BinaryTree<int> bt_test;

    bt_test.insert(37);
    bt_test.insert(19);
    bt_test.insert(51);
    bt_test.insert(55);
    bt_test.insert(4);
    bt_test.insert(11);
    bt_test.insert(20);
    bt_test.insert(2);
    std::cout<<bt_test;

    //bt_test.remove(11);
	//std::cout<<bt_test;
    //bt_test.remove(51);
    //bt_test.remove(19);
    //bt_test.remove(37);
    std::cout<<bt_test.getheight()<<'\n';

    return 0;
}
