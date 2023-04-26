#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
struct Node {
	T data;
	Node<T>* next;
	Node<T>(const T& data);
};

template <typename T>
class List {
    private:
        // Pointers to head and tail nodes
        Node<T>* head;
        Node<T>* tail;
    
    public:
        List<T>();
        ~List<T>();
        T front() const;
        T back() const;
        void add_front(T val);
        void add_back(T val);
        bool remove_front();
        
        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const List<U>& l);
};

// A single node in a Linked List
template <typename T>
Node<T>::Node(const T& data) {
	next = nullptr;
	this->data = data;
}

// Constructs list
template <typename T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
}

// Destructs list
template <typename T>
List<T>::~List() {
	Node<T>* current = head;
    while (head != nullptr) {
        current = head;
        head = head->next;
        delete current;
    }
}

// Returns data at list head
template <typename T>
T List<T>::front() const { return head->data; }

// Returns data at list tail
template <typename T>
T List<T>::back() const { return tail->data; }

// Adds new Node to front of list
template <typename T>
void List<T>::add_front(T val) {
    // Creates the new Node
    Node<T>* new_node = new Node<T>(val);
    
    // Sets new node as front of list
    new_node->next = head;
    head = new_node;
    
    // If list is empty, initialize tail pointer
    if (head->next == nullptr) { tail = new_node; }
}

// Adds new Node to back of list
template <typename T>
void List<T>::add_back(T val) {
   // Creates the new Node
    Node<T>* new_node = new Node<T>(val);
    
    // If list is empty, initialize head pointer
    if (tail == nullptr) { head = new_node; }
    
    // If list is not empty, add new Node to back
    else { tail->next = new_node; }
    
    // Resest tail pointer to point at back
    tail = new_node;
}

// Removes Node at front
// returns false if there's nothing to remove
template <typename T>
bool List<T>::remove_front() {
	if (head == nullptr) { return false; } // empty list
	
	// 1 element
	if (head == tail) {
		delete head;
		head = nullptr;
		tail = nullptr;
		return true;
	}
	
	// normal case
	Node<T>* old_head = head;
	head = head->next;
	delete old_head;
	
	return true;
}

// Output stream
template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& l) {
    if (l.head == nullptr) { return out; } // Guard clause
    
    // Output data then " "
    Node<T>* current = l.head;
    while (current->next != nullptr) {
        out << current->data << " ";
        current = current->next;
    }
    
    // Last value doesn't add a " "
    out << current->data;
    
    return out;
}



#endif
