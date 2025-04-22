// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& data) : data(data), next(nullptr) {}
  };
  Node* head;

 public:
  TPQueue() : head(nullptr) {}
  ~TPQueue() {
    while (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }
  void push(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
      head = newNode;
      return;
    }
    Node* current = head;
    Node* prev = nullptr;
    while (current && value.prior <= current->data.prior) {
      prev = current;
      current = current->next;
    }
    if (!prev) {
      newNode->next = head;
      head = newNode;
    } else {
      prev->next = newNode;
      newNode->next = current;
    }
  }
  T pop() {
    if (!head) {
      throw std::out_of_range("TPQueue is empty");
    }
    Node* temp = head;
    T data = temp->data;
    head = head->next;
    delete temp;
    return data;
  }
  const T& front() const {
    if (!head) {
      throw std::out_of_range("TPQueue is empty");
    }
    return head->data;
  }
  bool empty() const {
    return head == nullptr;
  }
};

struct SYM {
  har ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
