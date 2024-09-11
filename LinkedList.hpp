#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "ListNode.hpp"
//doubly linked list with pointers to next and prev
template <typename T>
class LinkedList{
  public:
    LinkedList() {
      //instantiate empty linked list
      front = NULL;
      back = NULL;
      size = 0;
    }
    ~LinkedList() {
      ListNode<T> *node = front;
      ListNode<T> *nodeToBeDeleted = front;
      while (node != NULL){
          nodeToBeDeleted = node->next;
          delete node;
          node = nodeToBeDeleted;
      }
    }
    void insertFront(T d) {
      ListNode<T> *node = new ListNode<T>(d);

      if(isEmpty()){
          back = node;
      }
      else{
          //not an empty list
          node->next = front;
          front->prev = node;
      }
      front = node;
      ++size;
    }
    void insertBack(T d) {
      ListNode<T> *node = new ListNode<T>(d);

      if(isEmpty()){
          front = node;
      }
      else{
          node->prev = back;
          back->next = node;
      }
      back = node;
      ++size;
    }
    T removeFront() {
      if(isEmpty()){
        throw runtime_error("list is empty");
      }

      ListNode<T> *temp = front;

      if(front->next == NULL){
        back = NULL;
      }
      else{
        //more than one node
        front->next->prev = NULL;
      }
      front = front->next;
      temp->next = NULL;
      T data = temp->data;
      --size;
      delete temp;

      return data;
    }
    T removeBack() {
      if(isEmpty()){
        throw runtime_error("list is empty");
      }

      ListNode<T> *temp = back;

      if(back->prev == NULL){
        front = NULL;
      }else{
        //more than one node
        back->prev->next = NULL;
      }
      back = back->prev;
      temp->prev = NULL;
      T data = temp->data;
      --size;
      delete temp;

      return data;
    }
    T find(T value) {
      int pos = -1; // variable to idetify position of node with matching value
      ListNode<T> *curr = front;

      while(curr != NULL){
          ++pos;
          if(curr->data == value)
              break;

          curr = curr->next;
      }
      if(curr == NULL)
          pos = -1;

      return pos;
    }
    //method for removing node not the front or the back
    T removeNode(T value) {
      if(isEmpty()){
        throw runtime_error("list is empty");
      }

      ListNode<T> *curr = front;
      while(curr->data != value){
        curr = curr->next;

        if(curr == NULL)
            return -1;
      }

      //if we get here, then we found the node to be deleted
      // so let's proceed

      if(getSize() == 1){
        front = NULL;
        back = NULL;
      }
      else if(curr == front){
        front = curr->next;
        front->prev = NULL;
      }
      else if(curr == back){
        back = curr->prev;
        back->next = NULL;
      }
      else{
        //current is between front and back
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
      }
      curr->next = NULL;
      curr->prev = NULL;
      T temp = curr->data;
      --size;
      delete curr;
      return temp;
    }
    unsigned int getSize() {
      return size;
    }
    bool isEmpty() {
      return (size == 0);
    }

    void printList(bool printLink) {
      ListNode<T> *curr = front;
      while(curr != 0){
         if(curr == front){
           cout << "{FRONT}: ";
         }
         else if(curr == back){
           cout << "{REAR}: ";
         }
         if(printLink)
          cout << "[ PREV: "<< curr->prev << " || " << curr->data << " || NEXT: "<< curr->next << " ] ";
        else
          cout << "[ " << curr->data << " ] ";

         curr = curr->next;
         if(curr != 0){
           cout << " <==> ";
         }
      }
      cout << endl;
    }
    
  private:
    ListNode<T> *front;
    ListNode<T> *back;
    unsigned int size;
};
#endif