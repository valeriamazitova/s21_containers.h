#include <gtest/gtest.h>

#include <list>

#include "s21_list.h"

class Testlist : public testing::Test {
 protected:
  std::list<int> list_empty;
  std::list<int> list = {1, 6, 3, 2, 5, 5};

  std::list<int> list_2 = {5, 4, 3, 2, 1};
  std::list<int> list_3 = list;

  s21::List<int> test_empty;
  s21::List<int> test = {1, 6, 3, 2, 5, 5};
  s21::List<int> test_2 = {5, 4, 3, 2, 1};
  s21::List<int> test_3 = test;
};

TEST_F(Testlist, test_empty) {
  EXPECT_EQ(list_empty.size(), test_empty.size());
  EXPECT_EQ(list_empty.empty(), test_empty.empty());
  EXPECT_EQ(list.empty(), test.empty());
}

TEST_F(Testlist, test_size) { EXPECT_EQ(list.size(), test.size()); }

TEST_F(Testlist, test_maxSize) { EXPECT_EQ(list.max_size(), test.max_size()); }

TEST_F(Testlist, push_back) {
  list_2.push_back(2);
  test_2.push_back(2);
  EXPECT_EQ(list_2.back(), test_2.back());
}

TEST_F(Testlist, push_front) {
  list_2.push_front(2);
  test_2.push_front(2);
  EXPECT_EQ(list_2.front(), test_2.front());
}

TEST_F(Testlist, reverse) {
  test.reverse();
  list.reverse();
  std::list<int>::iterator it;
  for (size_t i = 0; i < list.size(); i++) {
    it = std::next(list.begin(), i);
    EXPECT_EQ(*it, test[i]);
  }
}

TEST_F(Testlist, unique) {
  test.unique();
  list.unique();
  std::list<int>::iterator it;
  for (size_t i = 0; i < list.size(); i++) {
    it = std::next(list.begin(), i);
    EXPECT_EQ(*it, test[i]);
  }
}

TEST_F(Testlist, sort) {
  test.sort();
  list.sort();

  std::list<int>::iterator it;
  for (size_t i = 0; i < list.size(); i++) {
    it = std::next(list.begin(), i);
    EXPECT_EQ(*it, test[i]);
  }
}

TEST_F(Testlist, pop_back_and_pop_front) {
  test.pop_back();
  test.pop_front();
  list.pop_back();
  list.pop_front();

  std::list<int>::iterator it;
  for (size_t i = 0; i < list.size(); i++) {
    it = std::next(list.begin(), i);
    EXPECT_EQ(*it, test[i]);
  }
}

TEST_F(Testlist, swap) {
  test.swap(test_2);
  list.swap(list_2);

  std::list<int>::iterator it;
  for (size_t i = 0; i < list.size(); i++) {
    it = std::next(list.begin(), i);
    EXPECT_EQ(*it, test[i]);
  }
}

TEST_F(Testlist, insert) {
  test.insert(test.end(), 10);
  list.insert(list.end(), 10);

  std::list<int>::iterator it1;
  for (size_t i = 0; i < list.size(); i++) {
    it1 = std::next(list.begin(), i);
    EXPECT_EQ(*it1, test[i]);
  }
  test.insert(test.begin(), 10);
  list.insert(list.begin(), 10);

  std::list<int>::iterator it2;
  for (size_t i = 0; i < list.size(); i++) {
    it2 = std::next(list.begin(), i);
    EXPECT_EQ(*it2, test[i]);
  }

  test.insert(++test.begin(), 10);
  list.insert(++list.begin(), 10);

  std::list<int>::iterator it3;
  for (size_t i = 0; i < list.size(); i++) {
    it3 = std::next(list.begin(), i);
    EXPECT_EQ(*it3, test[i]);
  }
}

TEST_F(Testlist, splice) {
  test.splice(test.begin(), test_2);
  list.splice(list.begin(), list_2);

  std::list<int>::iterator it;
  for (size_t i = 0; i < list.size(); i++) {
    it = std::next(list.begin(), i);
    EXPECT_EQ(*it, test[i]);
  }
}

TEST_F(Testlist, merge) {
  test.merge(test_2);
  list.merge(list_2);

  std::list<int>::iterator it;

  for (size_t i = 0; i < list.size(); i++) {
    it = std::next(list.begin(), i);
    EXPECT_EQ(*it, test[i]);
  }
}
