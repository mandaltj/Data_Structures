#include <iostream>

template <typename T>
class LinkedList{
public:
	class Node {
	public:
		T data;
		Node *next;
		Node *prev;

		Node(): next(nullptr), prev(nullptr) {}
		Node(const T & data): data(data), next(nullptr), prev(nullptr) {}
	};
public:
	Node* Foo_do_something();
};

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Foo_do_something(){
	std::cout<<"Hello";
	Node *ptr = new Node(100);
	return ptr;
}

int main(){
	LinkedList<int> X;
	X.Foo_do_something();
	return 0;
}
