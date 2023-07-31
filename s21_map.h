#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_

#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class T>
class Map : BinaryTree<std::pair<Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<value_type>::Iterator;
  using const_iterator = typename BinaryTree<value_type>::ConstIterator;
  using size_type = std::size_t;

  Map() {}

  Map(std::initializer_list<value_type> const &items) : bt(items) {}

  Map(const Map &m) : BinaryTree<std::pair<Key, T>>(), bt(m.bt) {}

  Map(Map &&m) noexcept : bt(std::move(m.bt)) {}

  ~Map() {}

  Map &operator=(Map &&m) {
    bt = std::move(m.bt);
    return *this;
  }

  //        Map Element access
  T &at(const Key &key) {
    auto node = FindInMap(key);
    if (node == nullptr)
      throw std::out_of_range("The key does not exist in the map");
    return node->val.second;
  }

  T &operator[](const Key &key) {
    auto iter = FindInMap(key);
    if (iter == nullptr) {
      auto result = bt.insert(std::make_pair(key, T()));
      return result.first.get()->val.second;
    }
    return iter->val.second;
  }

  //        Map Iterators
  iterator begin() { return bt.begin(); }

  iterator end() { return bt.end(); }

  //        Map Capacity
  bool empty() { return bt.empty(); }

  size_type size() { return bt.size(); }

  size_type max_size() { return bt.max_size(); }

  //        Map Modifiers
  void clear() { bt.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return bt.insert(value);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return bt.insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto node = FindInMap(key);
    if (node) {
      node->val.second = obj;
      return std::make_pair(iterator(node), true);
    }
    return insert(key, obj);
  }

  void erase(iterator pos) { bt.erase(pos); }

  void swap(Map &other) { return bt.swap(other.bt); }

  void merge(Map &other) {
    s21::BinaryTree<value_type> tmp;
    iterator i = other.begin();
    while (i != other.end()) {
      if (!contains((*i).first)) {
        tmp.insert((*i));
        other.erase(i);
      }
      ++i;
    }
    bt.merge(tmp);
  }

  //        Map Lookup
  bool contains(const Key &key) {
    bool found = false;
    iterator i = begin();
    while (i != end() && !found) {
      if ((*i).first == key)
        found = true;
      else
        ++i;
    }
    return found;
  }

 private:
  BinaryTree<value_type> bt;

  typename s21::BinaryTree<value_type>::BTNode *FindInMap(const Key &key) {
    iterator i = begin();
    while (i != end()) {
      if ((*i).first == key) {
        return i.get();
      }
      ++i;
    }
    return nullptr;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_