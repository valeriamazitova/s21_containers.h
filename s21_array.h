#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_

#include <iostream>

namespace s21 {
template <class T, const size_t V>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using Iterator = T *;
  using const_Iterator = const T *;
  using size_type = size_t;

  Array() = default;

  Array(std::initializer_list<value_type> const &items) : Array() {
    if (items.size() > capacity_) {
      throw std::out_of_range("s21::Array::limit is exceeded");
    }
    int i = 0;
    for (auto element : items) {
      array_[i++] = element;
    }
  };

  Array(const Array &a) : Array() {
    int i = 0;
    for (auto element : a) {
      array_[i] = element;
      i = i + 1;
    }
  }

  Array(Array &&a) : Array() { std::move(a.begin(), a.end(), this->array_); }

  ~Array() = default;

  Array &operator=(Array &a) {
    std::swap(capacity_, a.capacity_);
    std::swap(array_, a.array_);
    return *this;
  }

  Array &operator=(Array &&a) {
    capacity_ = 0;
    fill(0);
    std::swap(capacity_, a.capacity_);
    std::swap(array_, a.array_);
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= capacity_) {
      throw std::out_of_range("s21::Array::limit is exceeded");
    }
    return array_[pos];
  }

  reference operator[](size_type pos) { return *(array_ + pos); }

  const_reference front() const { return *(array_); }

  const_reference back() const { return array_[capacity_ - 1]; }

  Iterator data() noexcept { return array_; }

  Iterator begin() noexcept { return array_; }

  Iterator end() noexcept { return array_ + capacity_; }

  const_Iterator begin() const { return array_; }

  const_Iterator end() const { return array_ + capacity_; }

  bool empty() {
    if (capacity_ == 0) return true;
    return false;
  }

  size_type size() { return capacity_; }

  size_type max_size() { return capacity_; }

  void swap(Array &other) {
    std::swap(array_, other.array_);
    std::swap(capacity_, other.capacity_);
  }

  void fill(const_reference value) {
    for (size_t i = 0; i < capacity_; i++) array_[i] = value;
  }

 private:
  value_type array_[V];
  size_type capacity_ = V;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_ARRAY_H_
