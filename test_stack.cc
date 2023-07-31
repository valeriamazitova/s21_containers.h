#include <gtest/gtest.h>

#include <stack>

#include "s21_stack.h"

TEST(StackTest, stack) {
  s21::Stack<int> n = {1, 2, 3, 4};
  s21::Stack<int> k(n);
  EXPECT_EQ(k.empty(), false);
  s21::Stack<int> l(std::move(k));
  s21::Stack<int> q;
  EXPECT_EQ(q.empty(), true);
  q = std::move(l);
  s21::Stack<int> m;
  m.swap(q);
  EXPECT_EQ(m.size(), 4);
  m.push(5);
  m.push(6);
  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(m.top(), i);
    m.pop();
  }
}
