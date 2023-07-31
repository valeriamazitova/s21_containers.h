#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_DEQUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_DEQUE_H_

#include <iostream>

namespace s21 {

template <class T>
class Deque {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  struct Node {
    value_type val;
    Node *prev;
    Node *next;
  };

  Deque() : head(nullptr), tail(nullptr), deq_size(0) {}

  Deque(std::initializer_list<value_type> const &items) : Deque() {
    for (auto i = items.begin(); i != items.end(); i++) {
      push_back(*i);
    }
  }

  Deque(const Deque &other) : Deque() {
    for (size_type i = 0U; i < other.size(); i++) {
      push_back(other[i]->val);
    }
  }

  Deque(Deque &&other) : Deque() { swap(other); }

  ~Deque() {
    if (!empty()) {
      Node *ptr = head;
      while (ptr) {
        Node *tmp = ptr->next;
        delete ptr;
        ptr = tmp;
      }
    }
    deq_size = 0;
  }

  Deque &operator=(Deque &&other) {
    swap(other);
    other.~Deque();
    return *this;
  }

  Node *operator[](const size_type index) const {
    if (head == nullptr) return nullptr;
    Node *tmp = head;
    for (size_type i = 0; i < index; i++) {
      tmp = tmp->next;
      if (tmp == nullptr) return nullptr;
    }
    return tmp;
  }

  const_reference begin() { return head->val; }

  const_reference end() { return tail->val; }

  bool empty() { return head == nullptr; }

  size_type size() const { return deq_size; }

  void push_back(const_reference val) {
    std::unique_ptr<Node> ptr(new Node());
    ptr.get()->val = val;
    if (empty()) {
      head = tail = ptr.get();
    } else {
      tail->next = ptr.get();
      ptr->prev = tail;
      tail = ptr.get();
    }
    ptr.release();
    deq_size++;
  }

  void push_front(const_reference val) {
    std::unique_ptr<Node> ptr(new Node());
    ptr.get()->val = val;
    if (empty()) {
      head = tail = ptr.get();
    } else {
      head->prev = ptr.get();
      ptr->next = head;
      head = ptr.get();
    }
    ptr.release();
    deq_size++;
  }

  Node *pop_back() {
    if (empty()) return nullptr;
    std::unique_ptr<Node> buff(tail);
    if (tail->prev == nullptr) {
      tail = head = nullptr;
    } else {
      tail = tail->prev;
    }
    deq_size--;
    return buff.get();
  }

  Node *pop_front() {
    if (empty()) return nullptr;
    std::unique_ptr<Node> buff(head);
    if (head->next == nullptr) {
      tail = head = nullptr;
    } else {
      head = head->next;
    }
    deq_size--;
    return buff.get();
  }

  void swap(Deque &other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(deq_size, other.deq_size);
  }

 private:
  Node *head;
  Node *tail;

  size_type deq_size;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_DEQUE_H_