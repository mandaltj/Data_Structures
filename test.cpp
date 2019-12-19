#include <cstdlib>
#include <chrono>

#include "LinkedList.h"
#include "catch/catch.hpp"

TEST_CASE("Benchmark: Testing Sorting Algorithms") {

  SECTION("Timing insertionSort") {

    constexpr int NUM_TEST_RUNS = 3;
    constexpr int LIST_SIZE_SMALL = 10;
    constexpr int LIST_SIZE_MEDIUM = 700;
    constexpr int LIST_SIZE_LARGE = LIST_SIZE_MEDIUM*10;

    LinkedList<int> unsortedList1;
    for (int i = LIST_SIZE_MEDIUM; i>0; i--) {
      unsortedList1.pushFront(i);
      unsortedList1.pushBack(i);
    }

    LinkedList<int> unsortedList2;
    for (int i = LIST_SIZE_LARGE; i>0; i--) {
      unsortedList2.pushFront(i);
      unsortedList2.pushBack(i);
    }

    // Reference for chrono library usage:
    // https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
    {
      std::cout << "Timing insertionSort:" << std::endl;
      LinkedList<int> sortedList;
      auto start_time = std::chrono::high_resolution_clock::now();
      for (int i=0; i<NUM_TEST_RUNS; i++) {
        //sortedList = unsortedList1.insertionSort();
        unsortedList1.insertionSort();
      }
      auto stop_time = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> dur_ms = stop_time - start_time;
      // Make sure the loop doesn't get optimized away.
      if (unsortedList1.getsize()) std::cout << "Time elapsed: " << dur_ms.count() << "ms" << std::endl;
	  //std::cout<<unsortedList1;
	}
    {
     std::cout << "Again, after increasing list size 10x:" << std::endl;
     LinkedList<int> sortedList;
     auto start_time = std::chrono::high_resolution_clock::now();
     for (int i=0; i<NUM_TEST_RUNS; i++) {
       //sortedList = unsortedList2.insertionSort
		unsortedList2.insertionSort();
     }
     auto stop_time = std::chrono::high_resolution_clock::now();
     std::chrono::duration<double, std::milli> dur_ms = stop_time - start_time;
     if (unsortedList2.getsize()) std::cout << "Time elapsed: " << dur_ms.count() << "ms" << std::endl;
     std::cout << "The worst case is O(n^2) for insertionSort, so the larger sort might take\n nearly 100x longer in this case." << std::endl;
    }
  }

  SECTION("Timing mergeSortRecursive") {

    constexpr int NUM_TEST_RUNS = 3;
    constexpr int LIST_SIZE_SMALL = 10;
    constexpr int LIST_SIZE_MEDIUM = 700;
    constexpr int LIST_SIZE_LARGE = LIST_SIZE_MEDIUM*10;

    LinkedList<int> unsortedList1;
    for (int i = LIST_SIZE_MEDIUM; i>0; i--) {
      unsortedList1.pushFront(i);
      unsortedList1.pushBack(i);
    }

    LinkedList<int> unsortedList2;
    for (int i = LIST_SIZE_LARGE; i>0; i--) {
      unsortedList2.pushFront(i);
      unsortedList2.pushBack(i);
    }

    LinkedList<int> unsortedListSmall;
    LinkedList<int> sortedListSmall;
    for (int i = LIST_SIZE_SMALL; i>0; i--) {
      unsortedListSmall.pushFront(i);
      unsortedListSmall.pushBack(i);
      sortedListSmall.pushFront(i);
      sortedListSmall.pushFront(i);
    }

    std::cout << std::endl;

    {
      // auto testSort = unsortedListSmall.MergeSortRecursive();
      unsortedListSmall.MergeSortRecursive();
      if (unsortedListSmall != sortedListSmall) {
        std::cout << "WARNING: It appears mergeSortRecursive or merge isn't correctly implemented yet.\n"
          << "  The running times below may not be meaningful." << std::endl;
      }
    }
    // Reference for chrono library usage:
    // https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
    {
      std::cout << "Timing mergeSortRecursive:" << std::endl;
      LinkedList<int> sortedList;
      auto start_time = std::chrono::high_resolution_clock::now();
      for (int i=0; i<NUM_TEST_RUNS; i++) {
        //sortedList = unsortedList1.MergeSortRecursive();
        unsortedList1.MergeSortRecursive();
      }
      auto stop_time = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> dur_ms = stop_time - start_time;
      // Make sure the loop doesn't get optimized away.
      if (unsortedList1.getsize()) std::cout << "Time elapsed: " << dur_ms.count() << "ms" << std::endl;
    }
    {
      std::cout << "Again, after increasing list size 10x:" << std::endl;
      LinkedList<int> sortedList;
      auto start_time = std::chrono::high_resolution_clock::now();
      for (int i=0; i<NUM_TEST_RUNS; i++) {
        //sortedList = unsortedList2.MergeSortRecursive();
        unsortedList2.MergeSortRecursive();
      }
      auto stop_time = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> dur_ms = stop_time - start_time;
      if (unsortedList2.getsize()) std::cout << "Time elapsed: " << dur_ms.count() << "ms" << std::endl;
      std::cout << "A correct implementation is O(n log n), so the larger sort should take\n about 11x-13x longer in this case." << std::endl;
    }
  }

}
