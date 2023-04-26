#ifndef STACK_H
#define STACK_H

#include "list.hpp"
#include <string>

template <typename T>
class Stack {
	private:
		List<T> data;
		int count;
	public:
		Stack();
		T top() const;
		int size() const;
		void push(T val);
		bool pop();
};

// initializes stack (only containing char)
template <typename T>
Stack<T>::Stack() {
	data = List<T>();
	count = 0;
}

// returns value at top of stack
template <typename T>
T Stack<T>::top() const { return data.front(); }

// returns size of stack
template <typename T>
int Stack<T>::size() const { return count; }

// adds new value to top of stack
template <typename T>
void Stack<T>::push(T val) {
	count++;
	data.add_front(val);
}

// removes top char from stack
// returns false if nothing was removed
template <typename T>
bool Stack<T>::pop() {
	bool popped = data.remove_front();
	if (popped) { count--; }
	return popped;
}

#endif
