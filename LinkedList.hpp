#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;

	// love these test cases
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const;
	Node<T>* getHead();
	const Node<T>* getHead() const;
	Node<T>* getTail();
	const Node<T>* getTail() const;

	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	void Clear();

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;

};

// Behaviors
template <typename T>
void LinkedList<T>::PrintForward() const {
	if (head == nullptr) return;
	Node<T>* curr = head;
	while (curr != nullptr) {
		std::cout << curr->data << std::endl;
		curr = curr->next;
	}
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
	if (tail == nullptr) return;
	Node<T>* curr = tail;
	while (curr != nullptr) {
		std::cout << curr->data << std::endl;
		curr = curr->prev;
	}
}

template <typename T>
void LinkedList<T>::printForward() const {
	PrintForward();
}

template <typename T>
void LinkedList<T>::printReverse() const {
	PrintReverse();
}

// Accessors
template <typename T>
[[nodiscard]] unsigned int LinkedList<T>::getCount() const {
	return count;
}

template <typename T>
Node<T>* LinkedList<T>::getHead() {
	return head;
};

template <typename T>
const Node<T>* LinkedList<T>::getHead() const {
	return head;
};

template <typename T>
Node<T>* LinkedList<T>::getTail() {
	return tail;
};

template <typename T>
const Node<T>* LinkedList<T>::getTail() const {
	return tail;
};

// Insertion
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
	Node<T>* new_head = new Node<T>{data, nullptr, head};
	if (head != nullptr) {
		head->prev = new_head;
	};
	head = new_head;
	count++;
	if (count == 1) {
		tail = head;
	}
};

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
	Node<T>* new_tail = new Node<T>{data, tail, nullptr};
	if (tail != nullptr) {
		tail->next = new_tail;
	};
	tail = new_tail;
	count++;
	if (count == 1) {
		head = tail;
	}
};

// Removal
template <typename T>
bool LinkedList<T>::RemoveHead() {
	if (count == 0) return false;
	if (count == 1) {
		Clear();
		return true;
	}
	Node<T>* new_head = head->next;
	new_head->prev = nullptr;
	delete head;
	head = new_head;
	count--;
	return true;
};

template <typename T>
bool LinkedList<T>::RemoveTail() {
	if (count == 0) return false;
	if (count == 1) {
		Clear();
		return true;
	}
	Node<T>* new_tail = tail->prev;
	new_tail->next = nullptr;
	delete tail;
	tail = new_tail;
	count--;
	return true;
};

template <typename T>
void LinkedList<T>::Clear() {
	// Free memory
	Node<T>* curr = head;
	while (curr != nullptr) {
		if (curr->next != nullptr) {
			curr = curr->next;
			delete curr->prev;
		} else {
			delete curr;
			curr = nullptr;
		}
	}
	// Set list to null state
	head = nullptr;
	tail = nullptr;
	count = 0;
};

// Operators
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
	// self-assignment guard
	if (&other == this) return *this;
	Clear();
	head = other.head;
	tail = other.tail;
	count = other.count;
	// Clean up other
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	// self-assignment guard
	if (&rhs == this) return *this;
	if (!rhs.head) { // guard for empty list
		Clear();
		return *this;
	}
	// Traverse through the list we want to copy
	Node<T>* _head = new Node<T>{rhs.head->data, nullptr, nullptr};
	int _count = 1;

	Node<T>* _curr = _head;
	Node<T>* list_curr = rhs.head;
	while (list_curr->next != nullptr) {
		_curr->next = new Node<T>{list_curr->next->data, _curr, nullptr};
		_count++;
		_curr = _curr->next;
		list_curr = list_curr->next;
	}
	// Traversal finished, clean up
	Clear();
	head = _head;
	tail = _curr;
	count = _count;
	return *this;
}

// Construction/Destruction
template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	if (!list.head) { // guard for empty list
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	// Traverse through the list we want to copy
	Node<T>* _head = new Node<T>{list.head->data, nullptr, nullptr};
	int _count = 1;

	Node<T>* _curr = _head;
	Node<T>* list_curr = list.head;
	while (list_curr->next != nullptr) {
		_curr->next = new Node<T>{list_curr->next->data, _curr, nullptr};
		_count++;
		_curr = _curr->next;
		list_curr = list_curr->next;
	}
	// Traversal finished, clean up
	head = _head;
	tail = _curr;
	count = _count;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
	head = other.head;
	tail = other.tail;
	count = other.count;
	// Clean up other
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Clear();
}