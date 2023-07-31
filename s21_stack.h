#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_STACK_H_

#include "s21_deque.h"

namespace s21 {
template <class T, class Container = Deque<T>>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  Stack() {}

  Stack(std::initializer_list<value_type> const &items) : c(items) {}

  Stack(const Stack &s) : c(s.c) {}

  Stack(Stack &&s) : c(std::move(s.c)) {}

  ~Stack() {}

  Stack &operator=(Stack &&s) {
    c = std::move(s.c);
    return *this;
  }

  const_reference top() { return c.end(); }

  bool empty() { return c.empty(); }

  size_type size() { return c.size(); }

  void push(const_reference value) { c.push_back(value); }

  void pop() { c.pop_back(); }

  void swap(Stack &other) { std::swap(c, other.c); }

 private:
  Container c;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_STACK_H_