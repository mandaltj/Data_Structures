#include <iostream>
#include "BinaryTree.h"
#include <chrono>

int main(){
    BinaryTree<int> bt_test;

    bt_test.insert(37);
    bt_test.insert(16);
    bt_test.insert(51);
    bt_test.insert(55);
    bt_test.insert(4);
	std::cout<<bt_test.isComplete()<<'\n';
	bt_test.insert(20);
	std::cout<<bt_test.isComplete()<<'\n';
	bt_test.insert(43);
	std::cout<<bt_test.isComplete()<<'\n';
	bt_test.insert(2);
	std::cout<<bt_test.isComplete()<<'\n';
	bt_test.insert(11);
	std::cout<<bt_test.isComplete()<<'\n';
	bt_test.insert(39);
	bt_test.insert(49);
	std::cout<<bt_test.isComplete()<<'\n';
	bt_test.insert(17);
	bt_test.insert(25);
	std::cout<<bt_test.isComplete()<<'\n';
	bt_test.remove(51);
	std::cout<<bt_test.isComplete()<<'\n';
	std::cout<<bt_test;

    //bt_test.remove(11);
	//std::cout<<bt_test;
    //bt_test.remove(51);
    //bt_test.remove(19);
    //bt_test.remove(37);
	//std::cout<<bt_test.isComplete()<<'\n';
	//bt_test.insert(52);
	//bt_test.insert(18);
	//std::cout<<bt_test.isComplete()<<'\n';
	//bt_test.insert(25);
	//std::cout<<bt_test.isComplete()<<'\n';
    return 0;
}
