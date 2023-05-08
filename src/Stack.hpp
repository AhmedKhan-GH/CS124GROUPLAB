#ifndef STACK_HPP
#define STACK_HPP
#include "Waypoint.hpp"
#include <string>

using namespace std;

class Node
{
private:
    Waypoint* data;
    Node* next;
friend class Stack;   
};

/**
   An implementation of a stack as a sequence of nodes.
*/
class Stack
{
public:   
   /** 
      Constructs an empty stack.
   */
   Stack();
   ~Stack();

   /**
      Adds an element to the top of the stack.
      @param element the element to add
   */
   void push(Waypoint* element);

   /**
      Yields the element on the top of the stack.
      @return the top element
   */
   Waypoint* top() const;

   /**
      Removes the element from the top of the stack.
   */
   void pop();

   /**
      Yields the number of elements in this stack.
      @return the size
   */
   int size() const;
  
private:   
   Node* first;
   int len;
};

#endif //STACK_HPP
