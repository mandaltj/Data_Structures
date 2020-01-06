This repository contains implementations of certain basic data structures. Learnt this through the Coursera online course:
https://www.coursera.org/specializations/cs-fundamentals from University of Illinois. It contains the following DS:-
1) LinkedList.h - Contains a LinkedList Class. Also has sorting member functions. This is a template class.
2) BinaryTree.h - Implementaion of a Binary Search Tree. Contains insertion and deletion features.
3) AVL.h - AVL tree implementation. Contains insertion and deletion features.

The primary objective is to learn the OOP aspect of C++ and certain basic data structures.
1) main_ll.cpp has certain codes which can be used to measure the runtime of a section of code. It uses "chrono" library.
2) The merge sort function in LinkedList.h sorts in-place. I struggled implementing it initially. But it's cool the way it
works in terms of pointers and stuff!!
3) Nothing out of the ordinary in the BinaryTree.h; But got good understanding of Contructors and Destructors. The remove
feature was something new for me. The functions remove() and swap() are particularly interesting.
4) AVL.h was slightly more complex than Binary tree because the insertion and removal require maintaining balance of the AVL.
Hence, the iop removal and the insertions are slight more complex. Interesting functions!!
5) In main_bt.cpp, added some code and comments about the "Rule of Three". Basically I didn't implement copy constructor in
my BinaryTree implementation. So when I used the copy method to initialize new BinaryTree instances, it did a shallow copy of
the internal nodes. Added the stackoverflow link as well.
