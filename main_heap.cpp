#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "Heap.h"

template <typename T>
void print_vec(const std::vector<T> & vec){
    std::cout<<"[";
    for(auto x: vec){
        std::cout<<x<<",";
    }
    std::cout<<"]\n";
}

int main(){
    int myarr[12] = {16, 15, 9, 25, 14, 7, 20, 6, 4, 12, 5, 11};

    Heap<int> hp;
    std::vector<int> vec;

    for(int i=0; i<12; i++){
        hp.insert(myarr[i]);
        vec.push_back(myarr[i]);
    }
    std::cout<<"Custom Heap Class: "<<hp<<"\n";
    std::make_heap(vec.begin(), vec.end(), std::greater<int>());
    std::cout<<"Heap from STL: ";
    print_vec(vec);

    //By this point you must have realized that the heap created by our Class
    //and the heap created by the std::make_heap are not same. At least, in terms
    // of structure they are not.

    //Let's compare the minremove functionality. This should match at everystep.
    for(int i=0; i<12; i++){
        int hp_val = hp.removeMin();
        int vec_val = vec.front();
        std::pop_heap(vec.begin(), vec.end(), std::greater<int>());
        vec.pop_back();
        //std::cout<<"hp_val: "<<hp_val<<" vec_val: "<<vec_val<<'\n';
        //print_vec(vec);
        if (hp_val != vec_val){
            std::runtime_error(std::string("Minimum value returned don't match"));
        }
    }

    //hp.insert(16);
    //hp.insert(15);
    //hp.insert(9);
    //hp.insert(25);
    //hp.insert(14);
    //hp.insert(7);
    //hp.insert(20);
    //hp.insert(6);
    //hp.insert(4);
    //hp.insert(12);
    //hp.insert(5);
    //hp.insert(11);

    //hp.removeMin();

    return 0;
}
