#include <iostream>
#include "LinkedList.h"
#include <chrono>

int main(){
	LinkedList<int> list_0;
	LinkedList<int> list_1;
	LinkedList<int> list_2;
	LinkedList<int> list_3;

	constexpr int LIST_SIZE_SMALL = 1000;
	constexpr int LIST_SIZE_LARGE = LIST_SIZE_SMALL*10;

	for(int i=0; i<LIST_SIZE_SMALL;i++){
		int temp = rand()%1000;
		list_0.pushBack(temp);
		list_1.pushBack(temp);
	}

	for(int i=0; i<LIST_SIZE_LARGE;i++){
		int temp = rand()%1000;
		list_2.pushBack(temp);
		list_3.pushBack(temp);
	}

	auto start_time = std::chrono::high_resolution_clock::now();
	list_0.insertionSort();
	//list_1.MergeSortRecursive();
	auto stop_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> dur_ms = stop_time - start_time;
	std::cout << "Time elapsed: " << dur_ms.count() << "ms" << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	list_1.MergeSortRecursive();
	stop_time = std::chrono::high_resolution_clock::now();
	dur_ms = stop_time - start_time;
	std::cout << "Time elapsed: " << dur_ms.count() << "ms" << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	list_2.insertionSort();
	stop_time = std::chrono::high_resolution_clock::now();
	dur_ms = stop_time - start_time;
	std::cout << "Time elapsed: " << dur_ms.count() << "ms" << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	list_3.MergeSortRecursive();
	stop_time = std::chrono::high_resolution_clock::now();
	dur_ms = stop_time - start_time;
	std::cout << "Time elapsed: " << dur_ms.count() << "ms" << std::endl;

	if(list_0==list_1){
		std::cout<<"Lists Same\n";
	}
	else{
		std::cout<<"Lists not Same\n";
	}
	if(list_2==list_3){
		std::cout<<"Lists Same\n";
	}
	else{
		std::cout<<"Lists not Same\n";
	}

	//list_0.pushBack(5);
	//list_0.pushBack(3);
	//list_0.pushBack(11);
	//list_0.pushBack(9);
	//list_0.pushBack(27);
	//list_0.pushBack(15);
	//list_0.pushBack(12);
	//list_0.pushBack(5);
	//list_0.pushBack(11);
	//list_0.pushBack(0);
	//list_1.pushBack(100);
	//list_1.pushBack(101);
	//list_1.pushBack(102);

	//std::cout<<list_0;
	//list_0.insertionSort();
	//list_0.MergeSortRecursive();
	//std::cout<<list_0;
	//auto sortedlist = list_0.insertionSort_new();
	//std::cout<<"List_0: "<<list_0;
	//std::cout<<"List_1: "<<list_1;
	//std::cout<<"List_1: "<<list_2;
	//list_2 = list_1 = list_0;
	//std::cout<<"After list_2=list_0=list_1: list_0 -> "<<list_0<<'\n';
	//std::cout<<"After list_2=list_0=list_1: list_1 -> "<<list_1<<'\n';
	//std::cout<<"After list_2=list_0=list_1: list_2 -> "<<list_2<<'\n';
	//list_1.pushBack("AAA");
	//std::string &temp_str = list_1.front();
	//temp_str = "BBB";
	//std::cout<<list_1;

	//list_0.pushBack(1);
	//list_0.pushBack(2);
	//list_0.pushBack(3);
	//list_0.pushBack(4);
	//std::cout<<list_0;
	//list_0.popFront();
	//list_0.popFront();
	//std::cout<<list_0;
	//list_0.pushBack(10);
	//list_0.pushBack(11);
	//std::cout<<list_0;
	//list_0.pushFront(99);
	//list_0.pushFront(100);
	//std::cout<<list_0;
	//list_0.popBack();
	//list_0.popBack();
	//std::cout<<list_0;

	//list_1.pushBack("AAA");
	//list_1.pushBack("BBB");
	//list_1.pushBack("CCC");
	//list_1.pushBack("DDD");
	//std::cout<<list_1;
	//list_1.pushFront("XAXA");
	//list_1.pushFront("KAKA");
	//std::cout<<list_1;
	//list_1.popFront();
	//list_1.popFront();
	//std::cout<<list_1;
	//list_1.popBack();
    //list_1.popBack();
	//std::cout<<list_1;

	return 0;
}
