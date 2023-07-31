#include <gtest/gtest.h>

#include <queue>

#include "s21_queue.h"

TEST(QueueTest, queue) {
  s21::Queue<int> n = {1, 2, 3, 4};
  s21::Queue<int> k(n);
  EXPECT_EQ(k.empty(), false);
  s21::Queue<int> l(std::move(k));
  s21::Queue<int> q;
  EXPECT_EQ(q.empty(), true);
  q = std::move(l);
  s21::Queue<int> m;
  m.swap(q);
  m.push(5);
  m.push(6);
  EXPECT_EQ(m.size(), 6);
  EXPECT_EQ(m.front(), 1);
  EXPECT_EQ(m.back(), 6);
  for (int i = 1; i < 7; i++) {
    EXPECT_EQ(m.front(), i);
    m.pop();
  }
}