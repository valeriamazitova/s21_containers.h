#include <gtest/gtest.h>

#include <iostream>
#include <map>

#include "s21_map.h"

TEST(MapTest1, Constructor) {
  std::map<std::string, int> m{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
  s21::Map<std::string, int> m1{{"CPU", 10}, {"GPU", 15}, {"RAM", 20}};

  EXPECT_EQ(m.empty(), m1.empty());
  EXPECT_EQ(m.size(), m1.size());
}

TEST(MapTest2, CopyConstructor) {
  std::map<int, char> m{{1, 'x'}, {2, 'y'}, {3, 'z'}};
  s21::Map<int, char> test_m{{1, 'x'}, {2, 'y'}, {3, 'z'}};

  std::map<int, char> m_copy(m);
  s21::Map<int, char> test_m_copy(test_m);

  EXPECT_EQ(m_copy.size(), test_m_copy.size());
  m_copy.clear();
  test_m_copy.clear();
  EXPECT_EQ(m_copy.size(), test_m_copy.size());
}

TEST(MapTest3, MoveConstructor) {
  std::map<int, std::string> c = {{1, "one"},  {2, "two"},  {3, "three"},
                                  {4, "four"}, {5, "five"}, {6, "six"}};
  s21::Map<int, std::string> test_c = {{1, "one"},  {2, "two"},  {3, "three"},
                                       {4, "four"}, {5, "five"}, {6, "six"}};

  std::map<int, std::string> c_copy(std::move(c));
  s21::Map<int, std::string> test_c_copy(std::move(test_c));
  s21::Map<int, std::string>::iterator i = test_c_copy.begin();
  for (auto it = c_copy.begin(); it != c_copy.end();) {
    if (it->first % 2 != 0 && (*i).first % 2 != 0) {
      it = c_copy.erase(it);
      test_c_copy.erase(i);
    } else {
      ++it;
      ++i;
    }
  }
  s21::Map<int, std::string>::iterator j = test_c_copy.begin();
  for (auto &p : c_copy) {
    ASSERT_TRUE(p.second == (*j).second);
    ++j;
  }
}

TEST(MapTest4, MoveAssignmentOperator) {
  std::map<std::string, std::string> m1{
      {"γ", "gamma"}, {"β", "beta"}, {"α", "alpha"}, {"γ", "gamma"}};

  s21::Map<std::string, std::string> test_m1{
      {"γ", "gamma"}, {"β", "beta"}, {"α", "alpha"}, {"γ", "gamma"}};

  std::map<std::string, std::string> m2;
  m2 = std::move(m1);
  s21::Map<std::string, std::string> test_m2;
  test_m2 = std::move(test_m1);

  EXPECT_EQ(m2.empty(), test_m2.empty());
  EXPECT_EQ(m2.size(), test_m2.size());
  EXPECT_EQ(m2.max_size(), test_m2.max_size());
}

TEST(MapTest5, swap) {
  std::map<std::string, std::string> m1 = {
      {"ε", "epsilon"}, {"δ", "delta"}, {"ε", "epsilon"}};
  s21::Map<std::string, std::string> test_m1 = {
      {"ε", "epsilon"}, {"δ", "delta"}, {"ε", "epsilon"}};

  size_t true_size = m1.size();

  EXPECT_EQ(m1.size(), test_m1.size());

  std::map<std::string, std::string> m2;
  s21::Map<std::string, std::string> test_m2;
  EXPECT_EQ(m2.size(), test_m2.size());

  m2.swap(m1);
  test_m2.swap(test_m1);

  EXPECT_EQ(true_size, m2.size());
  EXPECT_EQ(true_size, test_m2.size());
}

TEST(MapTest6, merge) {
  std::map<int, std::string> ma{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  std::map<int, std::string> mb{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  std::map<int, std::string> u;
  u.merge(ma);

  s21::Map<int, std::string> test_ma{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  s21::Map<int, std::string> test_mb{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  s21::Map<int, std::string> test_u;
  test_u.merge(test_ma);

  EXPECT_EQ(u.size(), test_u.size());
  EXPECT_EQ(ma.size(), test_ma.size());

  u.merge(mb);
  test_u.merge(test_mb);

  EXPECT_EQ(u.size(), test_u.size());
  EXPECT_EQ(mb.size(), test_mb.size());

  EXPECT_EQ(u.at(1), test_u.at(1));

  EXPECT_EQ(u[4], test_u[4]);
  EXPECT_EQ(u[5], test_u[5]);
  EXPECT_EQ(u[8], test_u[8]);
  EXPECT_EQ(u[10], test_u[10]);

  test_u[11] = "test";
  u[11] = "test";
  EXPECT_EQ(u[11], test_u[11]);
  ASSERT_TRUE(test_u[11] == "test");
}

TEST(MapTest7, contains) {
  std::map<int, char> example = {{1, 'a'}, {2, 'b'}};
  s21::Map<int, char> test_example = {{1, 'a'}, {2, 'b'}};

  ASSERT_TRUE(test_example.contains(2) == true);
  ASSERT_TRUE(test_example.contains(0) == false);
  ASSERT_TRUE(test_example.contains(1) == true);
}

TEST(MapTest8, insert) {
  std::map<int, char> example = {{1, 'a'}, {2, 'b'}};
  s21::Map<int, char> test_example = {{1, 'a'}, {2, 'b'}};

  example.insert({3, 'c'});
  example.insert({4, 'd'});
  test_example.insert({3, 'c'});
  test_example.insert(4, 'd');

  s21::Map<int, char>::iterator i = test_example.begin();
  for (auto it = example.begin(); it != example.end();) {
    EXPECT_EQ((*i), *it);
    ++i;
    ++it;
  }
}

TEST(MapTest9, insert_or_assign) {
  std::map<std::string, std::string> myMap;

  myMap.insert_or_assign("a", "apple");
  myMap.insert_or_assign("b", "banana");
  myMap.insert_or_assign("c", "cherry");
  myMap.insert_or_assign("c", "clementine");

  for (const auto &node : myMap) {
    std::cout << node.first << " " << node.second << "\n";
  }

  s21::Map<std::string, std::string> test_myMap;

  test_myMap.insert_or_assign("a", "apple");
  test_myMap.insert_or_assign("b", "banana");
  test_myMap.insert_or_assign("c", "cherry");
  test_myMap.insert_or_assign("c", "clementine");

  for (const auto &node : test_myMap) {
    std::cout << node.first << " " << node.second << "\n";
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}