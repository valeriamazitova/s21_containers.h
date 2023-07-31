#include <gtest/gtest.h>

#include <deque>

#include "s21_deque.h"

TEST(DequeTest1, deque) {
  s21::Deque<int> d;
  d.push_front(8);
  EXPECT_EQ(d.begin(), 8);
  d.push_front(9);
  EXPECT_EQ(d.begin(), 9);

  EXPECT_EQ(d.pop_back()->val, 8);
  EXPECT_EQ(d.pop_back()->val, 9);

  d.push_back(1);
  EXPECT_EQ(d.end(), 1);
  d.push_back(2);
  EXPECT_EQ(d.end(), 2);
}

TEST(DequeTest2, deque) {
  s21::Deque<double> d = {1.2, 3.4, 5.6, 7.8, 9.0};
  EXPECT_DOUBLE_EQ(d[2]->val, 5.6);
  EXPECT_EQ(d.size(), 5);
  s21::Deque<double> d_copy = d;

  std::deque<double> real_deque({1.2, 3.4, 5.6, 7.8, 9.0});
  for (auto i = 0U; i < d_copy.size(); i++) {
    EXPECT_DOUBLE_EQ(d_copy[i]->val, real_deque[i]);
  }
}

TEST(DequeTest3, deque) {
  s21::Deque<int> d = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(d.pop_front()->val, 1);
  s21::Deque<int> d_moved = std::move(d);

  std::deque<int> real_deque({2, 3, 4, 5, 6, 7, 8, 9});
  for (auto i = 0U; i < d_moved.size(); i++) {
    EXPECT_DOUBLE_EQ(d_moved[i]->val, real_deque[i]);
  }
}

TEST(DequeTest4, deque) {
  s21::Deque<int> d1 = {1, 2, 3};
  s21::Deque<int> d2 = {4, 5, 6, 7};
  d1.swap(d2);

  std::deque<int> real_deque1({1, 2, 3});
  std::deque<int> real_deque2({4, 5, 6, 7});
  real_deque1.swap(real_deque2);

  for (auto i = 0U; i < d1.size(); i++) {
    EXPECT_DOUBLE_EQ(d1[i]->val, real_deque1[i]);
  }

  for (auto i = 0U; i < d2.size(); i++) {
    EXPECT_DOUBLE_EQ(d2[i]->val, real_deque2[i]);
  }
}

TEST(DequeTest5, deque) {
  s21::Deque<std::string> d1 = {"hello", "my", "name", "is"};
  s21::Deque<std::string> d2;
  d2 = std::move(d1);

  std::deque<std::string> real_deque1({"hello", "my", "name", "is"});
  std::deque<std::string> real_deque2 = real_deque1;

  for (auto i = 0U; i < d2.size(); i++) {
    EXPECT_TRUE(d2[i]->val == real_deque2[i]);
  }
}

TEST(DequeTest6, deque) {
  s21::Deque<int> d = {0};
  EXPECT_EQ(d.pop_front()->val, 0);
}
