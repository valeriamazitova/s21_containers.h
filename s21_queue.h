#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_

#include "s21_deque.h"

namespace s21 {
template <class T, class Container = Deque<T>>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  Queue() {}

  Queue(std::initializer_list<value_type> const &items) : c(items) {}

  Queue(const Queue &q) : c(q.c) {}

  Queue(Queue &&q) : c(std::move(q.c)) {}

  ~Queue() {}

  Queue &operator=(Queue &&q) {
    c = std::move(q.c);
    return *this;
  }

  const_reference front() { return c.begin(); }

  const_reference back() { return c.end(); }

  bool empty() { return c.empty(); }

  size_type size() { return c.size(); }

  void push(const_reference value) { c.push_back(value); }

  void pop() { c.pop_front(); }

  void swap(Queue &other) { std::swap(c, other.c); }

 private:
  Container c;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_