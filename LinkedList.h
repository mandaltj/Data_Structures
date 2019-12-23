//pragma once directive makes sure that this header will be included only once
#pragma once
#include <iostream>

class Node;

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node *next;
        Node *prev;

        //Default constructor for Node Class
        Node(): next(nullptr), prev(nullptr) {}

        //Argument based constructor for Node Class
        Node(const T & data): data(data), next(nullptr), prev(nullptr) {}

        //= operator overload
        Node& operator=(const Node& other){
            this->next = other.next;
            this->prev = other.prev;
            this->data = other.data;
            return *this;
        }
    };
private:
    Node *head_;        //Pointer to head of LinkedList
    Node *tail_;        //Pointer to tail of LinkedList
    int size_;         //Size of the LinkedList

public:
    //Default Constructor for LinkedList Class
    LinkedList(): head_(nullptr), tail_(nullptr), size_(0) {}

    //Operator overload to Print out LinkedList
    std::ostream& print(std::ostream& os) const;

    //Operator for accessing the elements of a LinkedList
    T & operator[](int index);

    bool equals(const LinkedList<T> & other) const;

    bool operator==(const LinkedList<T> & other) const{
        return equals(other);
    }

    bool operator!=(const LinkedList<T> & other) const{
        return !equals(other);
    }

    //Operator= overload
    LinkedList<T>& operator=(const LinkedList<T> & other);

    //Push a new data item at the front of the LinkedList
    void pushFront(const T & newData);
    //Push a new data item at the back of the LinkedList
    void pushBack(const T & newData);
    //Pop a data item from the front of the LinkedList
    void popFront();
    //Pop a data item from the back of the LinkedList
    void popBack();

    //========================================================================
    //Functions for Sorting
    //========================================================================
    //This functions sorts the original LinkedList in place
    void insertionSort();
    void insertOrdered(Node* refNode);

    //This functions a new sorted LinkedList the original LinkedList is untouched
    LinkedList<T> insertionSort_new() const;
    void insertOrdered(const T& newData);

    ///This functions sorts the original LinkedList in place
    void MergeSortRecursive();
    void MergeSort(Node** startNode);
    void split(Node* startNode, Node** left_start_node, Node** right_start_node);
	Node* Merge(Node* left_start_node, Node* right_start_node);

	//=========================================================================
    //Check if the LinkedList is in sorted order or not
    bool isSorted() const;

    //Get the size of the LinkedList
    int getsize() const {return size_;}
    //Check if LinkedList is empty
    bool empty() const { return !head_; }

    void clear_list() {
        while(head_){
            popBack();
        }
    };

    ~LinkedList() {
        clear_list();
    };

};

//==========================================================================================
//                               Implementation
//==========================================================================================

//std::cout << operator overload for LinkedList
template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T> & ll){
    return ll.print(os);
}

template <typename T>
std::ostream& LinkedList<T>::print(std::ostream& os) const {
    os << "[ ";
    if (!head_){
        //return os empty
    } else {
        Node *thru = head_;
        while(thru){
            os << thru->data <<" ";
            thru = thru->next;
        }
    }
    os << "]\n";
    return os;
}

//Returns a reference to the "data" of a Node of LinkedList at "index".
//The reference can be used to change the "data" of the element.
template <typename T>
T & LinkedList<T>::operator[](int index){
    if((index>size_) || (index < 0)) throw std::runtime_error(std::string("index out of bounds"));
    Node *currNode = head_;
    while (index!=0){
        currNode = currNode->next;
        index--;
    }
    return currNode->data;
}

template <typename T>
//void LinkedList<T>::operator=(const LinkedList<T> & other) {
//Using void type only works with list_1=list_0 case but not with
//list_2=list_1=list_0
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> & other) {
    //First we clear out this present LinkedList
    clear_list();

    Node *other_currNode = other.head_;
    while(other_currNode){
        pushBack(other_currNode->data);
        other_currNode = other_currNode->next;
    }
    return *this;
}

template <typename T>
bool LinkedList<T>::equals(const LinkedList<T> & other) const{
    if (size_!=other.size_){
        return false;
    }
    // We'll iterate along both lists and check that all items match by value.
    const Node* thisCur  = head_;
    const Node* otherCur = other.head_;

    while (thisCur) {
        if (!otherCur) {
            throw std::runtime_error(std::string("Error in equals: ") + "otherCur missing a node or wrong item count");
        }
        if (thisCur->data != otherCur->data) {
            return false;
        }
        thisCur = thisCur->next;
        otherCur = otherCur->next;
    }

    return true;

}

template <typename T>
void LinkedList<T>::pushFront(const T & newData){
    Node *newNode = new Node(newData);

    if(!head_){
        //Since the LinkedList is empty only head_ and tail_ pointers need update
        head_ = newNode;
        tail_ = newNode;
    }
    else {
        //newNode points to the Node at head
        newNode->next = head_;
        //The old node at head has prev pointing to newNode
        head_->prev = newNode;
        //head_ now points to newNode
        head_ = newNode;
    }
    //Update Size
    size_++;
}

template <typename T>
void LinkedList<T>::pushBack(const T & newData){
    Node *newNode = new Node(newData);

    if(!head_){
        //Since the LinkedList is empty only head_ and tail_ pointers need update
        head_ = newNode;
        tail_ = newNode;
    }
    else {
        //The old node at tail has next pointing to newNode
        tail_->next = newNode;
        //newNode points to the Node at head
        newNode->prev = tail_;
        //head_ now points to newNode
        tail_ = newNode;
    }
    //Update Size
    size_++;
}

template <typename T>
void LinkedList<T>::popFront(){
    if(!head_){
        //Since the LinkedList is empty nothing to pop
        return;
    }
    else if (head_->next==nullptr) {
        //Only a single element in LinkedList
        delete head_;        //delete the single node element
        head_ = nullptr;    //head_ points to nullptr
        tail_ = nullptr;    //tail_ points to nullptr
        size_--;            //Update Size
        if (0 != size_) throw std::runtime_error(std::string("Error in popFront: Size not 0"));
        return;
    }

    //If we are here then this means that there are more than one element in
    //LinkedList. Need to update next Node pointers
    Node *currNode = head_;
    head_ = currNode->next;
    head_->prev = nullptr;
    delete currNode;
    //Well don't need to do this. Because when this function ends, currNode will
    //not exist anymore. But better to point it to nullptr just for safety. No harm!!
    currNode = nullptr;
    size_--;

}

template <typename T>
void LinkedList<T>::popBack(){
    if(!head_){
        //Since the LinkedList is empty nothing to pop
        return;
    }
    else if (tail_->prev==nullptr) {
        //Only a single element in LinkedList
        delete tail_;        //delete the single node element
        head_ = nullptr;    //head_ points to nullptr
        tail_ = nullptr;    //tail_ points to nullptr
        size_--;            //Update Size
        if (0 != size_) throw std::runtime_error(std::string("Error in popBack: Size not 0"));
        return;
    }

    Node *currNode = tail_;
    tail_ = currNode->prev;
    tail_->next = nullptr;
    delete currNode;
    currNode = nullptr;
    size_--;
}

template <typename T>
bool LinkedList<T>::isSorted() const {
    if(size_ < 2){
        return true;
    }

    Node *currNode = head_;
    while(currNode->next){
        if((currNode->data)>(currNode->next->data)){
            return false;
        }
        currNode = currNode->next;
    }
    return true;
}

template <typename T>
void LinkedList<T>::insertionSort() {
    //If size is 0 or 1 then no need to sort
    if (size_ < 2){
        return;
    }
    //int index = 1;

    Node *currNode = head_->next;
    while(currNode){
        //std::cout<<"Index: "<<index<<'\n';
        Node *nextNode = currNode->next;
        insertOrdered(currNode);
        //std::cout<<*this;
        currNode = nextNode;
        //index++;
    }
}

template <typename T>
void LinkedList<T>::insertOrdered(Node *refNode){
    Node *compareNode = head_;
    while(true){
        if(refNode->data < compareNode->data){
            if(refNode->next==nullptr){
                refNode->prev->next     = nullptr;
                //refnode->next->prev doesn't exist
                tail_                   = refNode->prev;
            } else {
                refNode->prev->next     = refNode->next;
                refNode->next->prev     = refNode->prev;
            }

            if(compareNode->prev==nullptr){
                refNode->prev       = nullptr;
                //compareNode->prev->next doesn't exist
                head_               = refNode;
            } else {
                refNode->prev           = compareNode->prev;
                compareNode->prev->next = refNode;
            }

            compareNode->prev         = refNode;
            refNode->next             = compareNode;

            return;
        }
        //If the compareNode->next is refNode; means refNode is the largest value.
        //Hence, no need to change anything
        if(compareNode->next == refNode){
            return;
        }

        //If we are here then it means that the currNode is compareNode than
        //the refNode. Need to check the next Node.
        //Update the compareNode pointer
        compareNode = compareNode->next;
    }
}

template <typename T>
LinkedList<T> LinkedList<T>::insertionSort_new() const {
    // Make result list
    LinkedList<T> result;

    // Walk along the original list and insert the items to the result in order.
    const Node* cur = head_;
    while (cur) {
        result.insertOrdered(cur->data);
        cur = cur->next;
    }
    return result;
}


template <typename T>
void LinkedList<T>::insertOrdered(const T& newData) {
  //Check if List is empty or not
  if (head_== nullptr){
      pushFront(newData);
      return;
  }

  //Get the current Node pointer. Starting at Head.
  Node *currNode = head_;
  while(true){
      if(newData < currNode->data){
          //Inserting at the front case
          if(currNode->prev==nullptr){
              pushFront(newData);
              return;
          }
          //else we are entering it somewhere in the middle case
          else{
              Node *newNode  = new Node(newData);
              Node *prevNode = currNode->prev;
              Node *nextNode = currNode;
              newNode->next  = nextNode;
              newNode->prev  = prevNode;
              prevNode->next = newNode;
              nextNode->prev = newNode;
              size_++;
              return;
          }
      }

      //If the currNode->next is nullptr; means newData is the largest value.
      //Hence, inserting at the back
      if(currNode->next == nullptr){
          pushBack(newData);
          return;
      }

      //If we are here then it means that the currNode is smaller than
      //the newData. Need to check the next Node.
      //Update the currNode pointer
      currNode = currNode->next;
  }
}

template <typename T>
void LinkedList<T>::MergeSortRecursive(){
    if (size_ < 2){
        return;
    }

    //std::cout<<"Item 0 Addr: "<<head_<<'\n';
    //std::cout<<"Item 1 Addr: "<<head_->next<<'\n';
    //std::cout<<"Item 2 Addr: "<<head_->next->next<<'\n';
    //std::cout<<"Item 3 Addr: "<<head_->next->next->next<<'\n';
    //std::cout<<"Item 4 Addr: "<<head_->next->next->next->next<<'\n';
    MergeSort(&head_);
    Node *currNode = head_;
    while (currNode->next!=nullptr){
        currNode = currNode->next;
    }
    tail_ = currNode;
}

template <typename T>
void LinkedList<T>::MergeSort(Node** startNode){

    if((*startNode)->next==nullptr){
        return;
    }

    Node* left_start_node     = nullptr;
    Node* right_start_node    = nullptr;

    //std::cout<<"===============================================================\n";
    //std::cout<<"Inside MergeSort\n";
    //std::cout<<"startNode Addr:"<<(*startNode)<<'\n';


    split(*startNode, &left_start_node, &right_start_node);
    //std::cout<<"left_start_node Addr:"<<left_start_node<<'\n';
    //std::cout<<"right_start_node Addr:"<<right_start_node<<'\n';
    MergeSort(&left_start_node);
    MergeSort(&right_start_node);
    *startNode = Merge(left_start_node, right_start_node);
}

template <typename T>
void LinkedList<T>::split(Node* startNode, Node** left_start_node, Node** right_start_node){
    //std::cout<<"Inside split\n";
    if(startNode->next==nullptr) throw std::runtime_error(std::string("split() error: startNode nullptr"));
    Node* slow = startNode;
    Node* fast = startNode;

    while(fast->next!=nullptr){
        fast = fast->next;
        if (fast->next!=nullptr){
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left_start_node  = startNode;
    *right_start_node = slow->next;

    (*left_start_node)->prev  = nullptr;
    slow->next                = nullptr;

    (*right_start_node)->prev = nullptr;
    fast->next                = nullptr;
}

// Node* Merge(Node* left_start_node, Node* right_start_node){
//     std::cout<<"Inside Merge\n";
//     if (left_start_node==nullptr){
//         return right_start_node;
//     }
//
//     if (right_start_node==nullptr){
//         return left_start_node;
//     }
//
//     Node* head_ptr = nullptr;
//
//     if(left_start_node->data<=right_start_node->data){
//         head_ptr = left_start_node;
//         head_ptr->next = Merge(left_start_node->next, right_start_node);
//         head_ptr->next->prev = head_ptr;
//     }
//     else{
//         head_ptr = right_start_node;
//         head_ptr->next = Merge(left_start_node, right_start_node->next);
//         head_ptr->next->prev = head_ptr;
//     }
//     return head_ptr;
// }

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Merge(Node* left_start_node, Node* right_start_node){
	//std::cout<<">>>>>>Inside Merge\n";
	//std::cout<<"left_start_node: "<<left_start_node<<'\n';
	//std::cout<<"right_start_node: "<<right_start_node<<'\n';

	Node* head_ptr;
	Node* main_thru;

	Node* left_thru  = left_start_node;
	Node* right_thru = right_start_node;
	bool first_time  = true;

	while(true){
		if(left_thru->data<=right_thru->data){
			if (first_time){
				head_ptr    = left_thru;
				main_thru   = left_thru;
				first_time  = false;
			}
			else{
				main_thru->next         = left_thru;
				main_thru->next->prev   = main_thru;
				main_thru               = main_thru->next;
			}
			left_thru = left_thru->next;
		}
		else{
			if (first_time){
				head_ptr    = right_thru;
				main_thru   = right_thru;
				first_time  = false;
			}
			else{
				main_thru->next         = right_thru;
				main_thru->next->prev   = main_thru;
				main_thru               = main_thru->next;
			}
			right_thru = right_thru->next;
		}

		if(left_thru==nullptr || right_thru==nullptr){
			break;
		}
	}


	if(left_thru==nullptr){
		//std::cout<<"left_thru null \n";
		main_thru->next = right_thru;
		main_thru->next->prev = main_thru;
	}
	else if(right_thru==nullptr){
		//std::cout<<"right_thru null \n";
		main_thru->next = left_thru;
		main_thru->next->prev = main_thru;
	}
	return head_ptr;
}
