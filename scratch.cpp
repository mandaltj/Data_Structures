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

void MergeSort(Node** startNode);
void split(Node* startNode, Node** left_start_node, Node** right_start_node);
Node* Merge(Node* left_start_node, Node* right_start_node);
