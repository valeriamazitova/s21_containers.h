#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_

#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class Container = BinaryTree<Key, std::less<Key>>>
class Set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Container::Iterator;
  using const_iterator = typename Container::ConstIterator;
  using size_type = size_t;

  // set member functions
  Set() {}

  Set(std::initializer_list<value_type> const &items) : bt(items) {}

  Set(const Set &s) : bt(s.bt) {}

  Set(Set &&s) : bt(std::move(s.bt)) {}

  ~Set() {}

  Set &operator=(Set &&s) {
    bt = std::move(s.bt);
    return *this;
  }

  // set iterators
  iterator begin() { return bt.begin(); }

  iterator end() { return bt.end(); }

  // set capacity
  bool empty() { return bt.empty(); }

  size_type size() { return bt.size(); }

  size_type max_size() { return bt.max_size(); }

  // set modifiers
  void clear() { bt.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return bt.insert(value);
  }

  void erase(iterator pos) { bt.erase(pos); }

  void swap(Set &other) { bt.swap(other.bt); }

  void merge(Set &other) { bt.merge(other.bt); }

  // set lookup
  iterator find(const Key &key) { return bt.find(key); }

  bool contains(const Key &key) { return bt.contains(key); }

 private:
  Container bt;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_