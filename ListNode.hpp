#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include <iostream>
using namespace std;

template <typename T>
class ListNode {
  public:
    ListNode() {
      next = NULL;
      prev = NULL;
    }
    ListNode(T d) {
      data = d;
      next = NULL;
      prev = NULL;
    }
    ~ListNode() {
      delete next;
      delete prev;
    }
    ListNode *next;
    ListNode *prev;
    T data;
};
#endif