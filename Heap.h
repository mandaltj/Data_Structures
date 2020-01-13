#pragma once
#include <iostream>

template <typename T>
class Heap{
public:
    Heap();

    //Insert an element
    void insert(const T& key);

    //Function to remove the minimum element
    T removeMin();

    //Operator overload to Print out LinkedList
    std::ostream& print(std::ostream& os) const;

    ~Heap();

private:
    unsigned size_;
    unsigned capacity_;
    T* item_;

    void heapifyDown_(unsigned index);
    void heapifyUp_(unsigned index);
    void growArray_();
    unsigned minChild_(unsigned index) const;
    void print_() const;
};

//==============================================================================
//                            Implementation
//==============================================================================

//std::cout << operator overload for LinkedList
template <typename T>
std::ostream& operator<<(std::ostream& os, const Heap<T> & hp){
    return hp.print(os);
}

template <typename T>
std::ostream& Heap<T>::print(std::ostream& os) const {
    os << "[ ";
    if (size_ > 0){
        for (unsigned i=1; i<=size_;i++){
            os<<item_[i]<<",";
        }
    }
    os << "]\n";
    return os;
}

template <typename T>
void Heap<T>::print_() const {
    std::cout << "[ ";
    if (size_ > 0){
        for (unsigned i=1; i<=size_;i++){
            std::cout<<item_[i]<<",";
        }
    }
    std::cout << "]\n";
}

//Constructor
template <typename T>
Heap<T>::Heap(){
    //Remember that heap is implemented using an Array
    //std::cout<<"Constructor Called\n";
    size_ = 0;
    capacity_ = 2;
    item_ = new T[capacity_+1];    //We need capacity_+1 because elements are inserted
                                //from index=1 and not 0
}

//Destructor
template <typename T>
Heap<T>::~Heap(){
    //std::cout<<"Destructor Called\n";
    delete [] item_;
}

//==============================================================================
//                        Insertion Implementation
//==============================================================================
template <typename T>
void Heap<T>::growArray_(){
    T* newitem = new T[(capacity_*2) + 1];
    //Notice that i starts from 1 and not 0
    for (unsigned i=1; i<=capacity_; i++){
        newitem[i] = item_[i];
    }
    capacity_ = capacity_*2;
    delete[] item_;
    item_ = newitem;
    //std::cerr << "Heap<T>::growArray_() increased array to capacity_ == " << capacity_ << std::endl;
}

template <typename T>
void Heap<T>::heapifyUp_(unsigned index){
    if (index==1){
        return;
    }

    if(item_[index] < item_[index/2]){
        std::swap(item_[index], item_[index/2]);
        heapifyUp_(index/2);
    }
}

template <typename T>
void Heap<T>::insert(const T& key){
    if (size_ == capacity_){
        growArray_();
    }

    size_++;                //Increase the size
    item_[size_] = key;        //Inserting the element
    heapifyUp_(size_);        //Ensure that the heap structure is maintained
}

//==============================================================================
//                        Remove Implementation
//==============================================================================
template <typename T>
void Heap<T>::heapifyDown_(unsigned index){
    if (index*2>size_){
        //This is a leaf index
        return;
    }

    unsigned minIndex = minChild_(index);
    if (item_[index] > item_[minIndex]){
        std::swap(item_[index], item_[minIndex]);
        //print_();
        heapifyDown_(minIndex);
    }
}

template <typename T>
unsigned Heap<T>::minChild_(unsigned index) const{
    unsigned left = index*2;
    unsigned right = (index*2) + 1;

    if (right > size_){
        return left;
    }
    else if (item_[left] < item_[right]){
        return left;
    }
    else{
        return right;
    }
}

template <typename T>
T Heap<T>::removeMin(){
    T minValue = item_[1];
    std::swap(item_[1], item_[size_]);
    size_--;
    //print_();
    heapifyDown_(1);
    return minValue;
}
