#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_

#include <iostream>

namespace s21 {

template <typename T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  class Node {
   public:
    value_type val_;
    Node *prev_;
    Node *next_;
    Node() : val_(), prev_(nullptr), next_(nullptr) {}
    Node(const value_type value)
        : val_(value), prev_(nullptr), next_(nullptr) {}
    Node(const Node &other) = delete;
    Node(const Node &&other) = delete;
    ~Node() = default;
  };

  class ListIterator {
    friend List;

   public:
    ListIterator() = default;
    ListIterator(Node *ptr) : ptr(ptr) {}

    reference operator*() const { return ptr->val_; }

    value_type *operator->() const { return &ptr->val_; }

    ListIterator &operator++() {
      ptr = ptr->next_;
      return *this;
    }

    bool operator==(const ListIterator &other) { return ptr == other.ptr; }

    bool operator!=(const ListIterator &other) { return ptr != other.ptr; }

    bool operator<(const ListIterator &other) const { return ptr < other.ptr; }

    bool operator>=(const ListIterator &other) const {
      return ptr >= other.ptr;
    }

    ListIterator operator++(int) {
      ListIterator tmp = *this;
      ptr = ptr->next_;
      return tmp;
    }

    ListIterator operator--(int) {
      ListIterator tmp = *this;
      ptr = ptr->prev_;
      return tmp;
    }

   private:
    Node *ptr;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator() {}
    ListConstIterator(const ListIterator &ptr) : ListIterator(ptr) {}

    ListConstIterator operator=(const ListConstIterator &ptr) {
      ListIterator::operator=(ptr);
      return *this;
    }
    const_reference operator*() const { return ListIterator::operator*(); }
  };

 public:
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  const_iterator cbegin() const { return const_iterator(head_); }
  const_iterator cend() const { return const_iterator(tail_->next_); }

  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(tail_->next_); }

  List() {
    size_ = 0;
    head_ = tail_ = nullptr;
  };

  List(size_type n) : List() {
    for (size_type i = 0; i < n; ++i) push_back(value_type());
  };

  List(std::initializer_list<value_type> const &items) : List() {
    for (auto &item : items) {
      push_back(item);
    }
  }

  List(const List &l) : List() {
    for (auto it = l.cbegin(); it != l.cend(); ++it) {
      push_back(*it);
    }
  }

  List(List &&l) : List() { swap(l); }

  ~List() { clear(); };

  void clear() {
    while (head_ != nullptr) {
      pop_front();
    }
  }

  List &operator=(List &l) {
    for (int i = 0; i < this->size_; ++i) {
      push_back(l[i]->val_);
    }
    return *this;
  }

  List &operator=(List &&l) {
    swap(l);
    l.clear();
    return *this;
  }

  const_reference back() { return tail_->val_; }

  const_reference front() { return head_->val_; }

  void swap(List &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  Node *push_front(value_type data) {
    Node *ptr = new Node(data);
    ptr->next_ = head_;
    if (head_ != nullptr) {
      head_->prev_ = ptr;
    }
    if (tail_ == nullptr) {
      tail_ = ptr;
    }
    ++size_;
    head_ = ptr;
    return ptr;
  };

  Node *push_back(value_type data) {
    Node *ptr = new Node(data);
    ptr->prev_ = tail_;
    if (tail_ != nullptr) {
      tail_->next_ = ptr;
    }
    if (head_ == nullptr) {
      head_ = ptr;
    }
    ++size_;
    tail_ = ptr;
    return ptr;
  };

  void pop_front() {
    if (head_ == nullptr) return;
    Node *ptr = head_->next_;
    if (ptr != nullptr)
      ptr->prev_ = nullptr;
    else
      tail_ = nullptr;
    delete head_;
    head_ = ptr;
    --size_;
  }

  void pop_back() {
    if (tail_ == nullptr) return;
    Node *ptr = tail_->prev_;
    if (ptr != nullptr)
      ptr->next_ = nullptr;
    else
      head_ = nullptr;
    delete tail_;
    tail_ = ptr;
    --size_;
  }

  value_type operator[](int index) { return At(index); }

  value_type At(size_type index) {
    Node *ptr = head_;
    size_type n = 0;
    while (n != index) {
      if (ptr == nullptr) return ptr->val_;
      ptr = ptr->next_;
      ++n;
    }
    return ptr->val_;
  }

  void reverse() {
    if (size_ < 2) return;
    Node *ptr = head_;
    for (int i = 0; i < size_; ++i) {
      std::swap(ptr->prev_, ptr->next_);
      ptr = ptr->prev_;
    }
    std::swap(head_, tail_);
  };

  bool empty() {
    if (head_ == nullptr)
      return true;
    else
      return false;
  }

  size_type size() { return size_; }

  size_type max_size() {
    size_type max_size =
        (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
    return max_size;
  }

  void unique() {
    for (iterator iter = this->begin(); iter != this->end();) {
      iterator iter2 = iter;
      ++iter2;
      if (iter2.ptr == nullptr) {
        return;
      } else if (*iter == *(iter2)) {
        erase(iter2);
      } else {
        ++iter;
      }
    }
  }

  void sort() {
    for (iterator it = this->begin(); it != this->end(); ++it) {
      iterator pos = it;
      ++pos;
      for (; pos != this->end(); ++pos) {
        if (*it > *pos) std::swap(*pos, *it);
      }
    }
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos == begin()) {
      push_front(value);
      pos = head_;
    } else if (pos == end()) {
      push_back(value);
      pos = tail_;
    } else {
      Node *element = pos.ptr;
      Node *convertion = new Node(value);
      convertion->next_ = element;
      convertion->prev_ = element->prev_;
      element->prev_->next_ = convertion;
      element->prev_ = convertion;
      this->size_++;
      return iterator(convertion);
    }
    return (pos);
  }

  void splice(const_iterator pos, List &other) {
    for (iterator iter = other.begin(); iter != other.end(); ++iter) {
      this->insert(pos, *iter);
    }
  }

  void merge(List &other) {
    if (this != &other) {
      iterator oit = other.begin();
      iterator it = this->begin();
      while (!other.empty()) {
        if (it == this->end()) {
          this->insert(it, *oit);
          other.erase(oit);
          ++oit;
        } else if (*oit < *it) {
          this->insert(it, *oit);
          other.erase(oit);
          ++oit;
        } else {
          ++it;
        }
      }
    }
  }

  void erase(iterator pos) {
    std::unique_ptr<Node> ptr(pos.ptr);
    if (ptr.get() == head_ && ptr.get() == tail_) {
      head_ = tail_ = nullptr;
    } else if (ptr.get() == head_) {
      head_ = head_->next_;
      head_->prev_ = nullptr;
    } else if (ptr.get() == tail_) {
      tail_ = tail_->prev_;
      tail_->next_ = nullptr;
    } else {
      ptr->next_->prev_ = ptr->prev_;
      ptr->prev_->next_ = ptr->next_;
    }
    --size_;
  }

 private:
  int size_;
  Node *head_;
  Node *tail_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_LIST_H_
