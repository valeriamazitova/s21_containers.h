#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_VECTOR_H_

#include <iostream>

namespace s21 {

template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector() {
    this->size_ = 0;
    this->capacity_ = 0;
    this->array = nullptr;
  }

  Vector(size_type n) {
    this->size_ = n;
    this->capacity_ = n;
    this->array = new value_type[n];
  }

  Vector(std::initializer_list<value_type> const &items) {
    size_ = items.size();
    capacity_ = items.size();
    array = new value_type[capacity_];
    std::copy(items.begin(), items.end(), array);
  }

  Vector(const Vector &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    array = new T[capacity_];
    std::copy(v.array, v.array + v.size_, array);
  }

  Vector(Vector &&v) noexcept {
    size_ = v.size_;
    capacity_ = v.capacity_;
    array = v.array;
    v.size_ = 0;
    v.capacity_ = 0;
    v.array = nullptr;
  }

  ~Vector() {
    if (this->array) {
      delete[] this->array;
    }
    this->array = nullptr;
    this->size_ = this->capacity_ = 0;
  }

  Vector &operator=(Vector &&v) noexcept {
    if (this != &v) {
      delete[] array;
      size_ = v.size_;
      capacity_ = v.capacity_;
      array = v.array;
      v.size_ = 0;
      v.capacity_ = 0;
      v.array = nullptr;
    }
    return *this;
  }

  reference at(size_type pos) {
    return (pos >= this->size_) ? throw std::out_of_range("Invalid index")
                                : this->array[pos];
  }

  reference operator[](size_type pos) {
    size_type less_zero = 0;
    if (this->size() < pos || less_zero > pos) {
      throw std::out_of_range("Index out of range");
    }
    return array[pos];
  }

  reference operator[](size_type pos) const {
    size_type less_zero = 0;
    if (this->size() < pos || less_zero > pos) {
      throw std::out_of_range("Index out of range");
    }
    return array[pos];
  }

  const_reference front() {
    return this->empty() ? throw std::out_of_range("Out of range") : array[0];
  }

  const_reference back() {
    return this->empty() ? std::out_of_range("Out of range") : array[size_ - 1];
  }

  value_type *data() { return array; }

 public:
  iterator begin() noexcept { return array; }

  iterator end() noexcept { return array + size_; }

  const_iterator begin() const noexcept { return array; }

  const_iterator end() const noexcept { return array + size_; }

 public:
  bool empty() const { return size_ != 0 ? false : true; }

  size_type size() { return size_; };

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2u;
  }

  void reserve(size_type size) {
    if (size <= capacity_) {
      return;
    }

    value_type *newArray = new value_type[size];

    if (array != nullptr) {
      for (size_type i = 0; i < size_; ++i) {
        newArray[i] = array[i];
      }

      delete[] array;
    }

    array = newArray;
    capacity_ = size;
  }

  size_type capacity() const { return capacity_; }

  void shrink_to_fit() {
    if (size_ == capacity_) {
      return;
    }

    if (size_ == 0) {
      delete[] array;
      array = nullptr;
      capacity_ = 0;
    } else {
      value_type *newArray = new value_type[size_];

      for (size_type i = 0; i < size_; ++i) {
        newArray[i] = array[i];
      }

      delete[] array;
      array = newArray;
      capacity_ = size_;
    }
  }

 public:
  void clear() {
    this->size_ = 0;
    this->capacity_ = 0;
    this->array = {nullptr};
  }

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - begin();

    if (size_ == capacity_) {
      size_type newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
      reserve(newCapacity);
    }

    if (index < size_) {
      for (size_type i = size_; i > index; --i) {
        array[i] = array[i - 1];
      }
    }

    array[index] = value;
    ++size_;

    return begin() + index;
  }

  void erase(iterator pos) {
    if (pos >= begin() && pos < end()) {
      size_type index = pos - begin();

      for (size_type i = index; i < size_ - 1; ++i) {
        array[i] = array[i + 1];
      }

      --size_;

      array[size_].~value_type();
    }
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      size_type newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
      reserve(newCapacity);
    }

    array[size_] = value;
    ++size_;
  }

  void pop_back() {
    if (size_ > 0) {
      --size_;
    }
  }

  void swap(Vector &other) {
    size_type tempSize = size_;
    size_ = other.size_;
    other.size_ = tempSize;

    size_type tempCapacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tempCapacity;

    value_type *tempArray = array;
    array = other.array;
    other.array = tempArray;
  }

 private:
  value_type *array;
  size_type size_;
  size_type capacity_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_VECTOR_H_
