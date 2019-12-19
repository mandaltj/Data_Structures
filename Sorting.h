#pragma once
#include <iostream>
#include "LinkedList.h"

template <typename T>
void swap( T &X, T &Y );

//Templated function for insertion Sort. Takes a pointer to an array/LinkedList
//as argument. Sorts the array/LinkedList itself.
template <typename T>
void insertSort( T *X );

//==============================================================================
//                            Implementation
//==============================================================================
template <typename T>
void swap( T &X, T &Y ){
    T temp = X;
    X = Y;
    Y = temp;
}

template <typename T>
void insertSort( LinkedList<T> X, int size ){
    for(int i=1; i<size; i++){
        int slot = i;
        for(int j=i-1; j>0; j--){
            //if(X[slot]<X[j]){
            //    swap(X[slot], X[j]);
            //    slot = j;
            //}
			if(X[slot]>=X[j]){
				break;
			}
			else if{(X[slot]<X[j]) && (X[slot]>=X[j-1])

			}
        }
    }
};
