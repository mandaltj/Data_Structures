#include <iostream>
#include "BinaryTree.h"
#include <chrono>

int main(){
    //BinaryTree<int> bt_1;

    //bt_1.insert(37);
    //bt_1.insert(16);
    //bt_1.insert(51);
    //bt_1.insert(55);
    //bt_1.insert(20);
    //bt_1.insert(4);
    //bt_1.insert(2);
    //bt_1.insert(11);
    //std::cout<<"bt_1 after inserting elements:\n";
    //std::cout<<"bt_1: "<<bt_1<<'\n';

    //bt_1.remove(16);
    //std::cout<<"bt_1 after deleting element:"<<16<<"\n";
    //std::cout<<"bt_1: "<<bt_1<<'\n';

    //==========================================================================
    //Rule of Three:https://stackoverflow.com/a/4172724/4422502
    //==========================================================================

	//If you need to explicitly declare either the destructor, copy constructor
    //or copy assignment operator yourself, you probably need to explicitly
    //declare all three of them.

    //We have a nice BinaryTree bt_1. Let's use the copy constructor to create
    //a new binary tree bt_2 from bt_1
    //BinaryTree<int> bt_2(bt_1);
    //std::cout<<"bt_2: "<<bt_2<<'\n';

    //If you compile only upto the above line you will face the following error:
    //Error: double free or corruption (fasttop)
    //(Assuming there is no code after this)
    //This is because the following sequence of incidents:
    //First, the bt_1 destructor is called, deleting all its nodes
    //Second, the bt_2 destructor is called, trying to delete all its nodes. But
    //that's where the issue is.
    //You see, the copy constructor does a shallow copy of the nodes. So, bt_1's
    //destructor not only deleted bt_1's nodes but also bt_2's nodes.

    //To verify that the copy constructor did a shallow copy, let's try to remove
    //a node from bt_1 and see if that reflects in bt_2 or not. If by changing bt_1,
    //a change is observed in bt_2 that means that we have a default copy constructor
    //doing a shallow copy.

    //The following lines of code will work as commented only if a copy constructor
    //is not implemented. If you want to study the behavior, then comment the copy
    //constructor then run the following lines of code.

    //bt_1.remove(2);            //Deleting a Leaf Node
    //std::cout<<"bt_1: \n";
    //bt_1.printInOrder();
    //std::cout<<"bt_2: \n";
    //bt_2.printInOrder();
    //After this you will observe that both bt_1 and bt_2 have there nodes deleted.
    //Hmmmm!! that's not good.

    //bt_1.remove(37);        //Deleting Root Node
    //std::cout<<"bt_1: \n";
    //bt_1.printInOrder();
    //std::cout<<"bt_2: \n";
    //bt_2.printInOrder();
    //After this you will observe that bt_2 just becomes some garbage. It is because.

    //when we deleted the node root of bt_1 for removing it, we also deleted the node
    //root of bt_2. Absolute Disaster!!


    //Beyond this point it is assumed that a copy constructor has been implemented
    //One way to solve this is to explicitly define our copy constructor. This
    //copy constructor will explicitly create new nodes and then traverse the passed
    //BinaryTree(bt_1 in our case) and add elements one by one to the new BinaryTree
    //(bt_2 in our case). That's tedious!!!

    BinaryTree<int> bt_3;

    bt_3.insert(37);
    bt_3.insert(16);
    bt_3.insert(51);
    bt_3.insert(55);
    bt_3.insert(20);
    bt_3.insert(4);
    bt_3.insert(2);
    bt_3.insert(11);

    BinaryTree<int> bt_4(bt_3);
    std::cout<<bt_3<<'\n';
    std::cout<<bt_4<<'\n';

    //Deleting leaf node 2 from bt_3
    bt_3.remove(2);
    std::cout<<"Leaf Node 3 deleted from bt_3\n";
    std::cout<<bt_3<<'\n';
    std::cout<<bt_4<<'\n';

    //Deleting root node 37 from bt_3
    bt_3.remove(37);
    std::cout<<"Root Node 37 deleted from bt_3\n";
    std::cout<<bt_3<<'\n';
    std::cout<<bt_4<<'\n';

    //TODO:Similarly we need to define a copy assignment constructr as well
    //That's peding will do it someday !!!

    return 0;
}
