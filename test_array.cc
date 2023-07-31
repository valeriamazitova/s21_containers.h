#include <gtest/gtest.h>

#include <list>

#include "s21_array.h"

class TestArray : public testing::Test {
 protected:
  s21::Array<int, 0> array_empty;
  s21::Array<int, 5> array = {1, 2, 3, 4, 5};
  s21::Array<int, 5> array_2 = {5, 4, 3, 2, 1};
  s21::Array<int, 5> array_3 = array;

  std::array<int, 0> test_empty;
  std::array<int, 5> test = {1, 2, 3, 4, 5};
  std::array<int, 5> test2 = {5, 4, 3, 2, 1};
  std::array<int, 5> test3 = test;
};

TEST_F(TestArray, test_constructor_def) {
  EXPECT_EQ(array_empty.size(), test_empty.size());
}

TEST_F(TestArray, test_constructor_il) {
  EXPECT_EQ(array.size(), test.size());
  for (size_t i = 0; i < array.size(); i++) EXPECT_EQ(array.at(i), test.at(i));
}

TEST_F(TestArray, test_constructor_cpy) {
  EXPECT_EQ(array_3.size(), test3.size());
  for (size_t i = 0; i < array_3.size(); ++i)
    EXPECT_EQ(array_3.at(i), test3.at(i));
}

TEST_F(TestArray, test_constructor_move) {
  s21::Array<int, 5> array_4 = std::move(array);
  std::array<int, 5> test4 = std::move(test);
  EXPECT_EQ(array_4.size(), test4.size());
  for (size_t i = 0; i < array_4.size(); ++i)
    EXPECT_EQ(array_4.at(i), test4.at(i));
}

TEST_F(TestArray, test_op_move) {
  s21::Array<int, 5> arr = {1, 2, 3, 4, 5};
  array_2 = std::move(arr);
  test2 = std::move(test);
  EXPECT_EQ(array_2.size(), test2.size());
  for (size_t i = 0; i < array_2.size(); ++i)
    EXPECT_EQ(array_2.at(i), test2.at(i));
}

TEST_F(TestArray, test_size) {
  EXPECT_EQ(array.size(), test.size());
  EXPECT_EQ(array_empty.size(), test_empty.size());
}

TEST_F(TestArray, test_empty) {
  EXPECT_EQ(array.empty(), test.empty());
  EXPECT_EQ(array_empty.empty(), test_empty.empty());
  EXPECT_NE(array.empty(), test_empty.empty());
}

TEST_F(TestArray, test_max_size) {
  EXPECT_EQ(array.max_size(), test.max_size());
  EXPECT_EQ(array_empty.max_size(), test_empty.max_size());
}

TEST_F(TestArray, test_swap) {
  array.swap(array_2);
  test.swap(test2);
  EXPECT_EQ(array.size(), test.size());
  for (size_t i = 0; i < array.size(); ++i) EXPECT_EQ(array.at(i), test.at(i));
}

TEST_F(TestArray, test_fill) {
  array.fill(-1);
  test.fill(-1);
  for (size_t i = 0; i < array.size(); ++i) EXPECT_EQ(array.at(i), test.at(i));
  array_empty.fill(5);
  test_empty.fill(5);
  EXPECT_NO_THROW(array_empty.fill(5));
  EXPECT_NO_THROW(test_empty.fill(5));
}

TEST_F(TestArray, test_front) { EXPECT_EQ(array.front(), test.front()); }

TEST_F(TestArray, test_back) { EXPECT_EQ(array.back(), test.back()); }

TEST_F(TestArray, test_data) {
  EXPECT_EQ(array.data(), &array.front());
  EXPECT_EQ(test.data(), &test.front());
}

TEST_F(TestArray, test_it_begin) { EXPECT_EQ(*array.begin(), *test.begin()); }

TEST_F(TestArray, test_it_end) {
  EXPECT_EQ(*(array.end() - 1), *(test.end() - 1));
}

TEST_F(TestArray, test_op_brck) {
  EXPECT_EQ(array[3], test[3]);
  EXPECT_NO_THROW(array[10]);
  EXPECT_NO_THROW(test[10]);
}

TEST_F(TestArray, test_at) { EXPECT_EQ(array.at(3), test.at(3)); }
