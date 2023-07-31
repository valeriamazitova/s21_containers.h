#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "s21_set.h"

TEST(SetTest1, iterator) {
  s21::Set<int> ss = {1, 2, 2, 2, 2};

  for (const auto &i : ss) {
    std::cout << i << "\n";
  }

  std::set k = {1, 2, 2, 2, 2};
  for (const auto &i : k) {
    std::cout << i << "\n";
  }
}

TEST(SetTest2, MoveAssignmentOperator) {
  s21::Set<double> set1;
  s21::Set<double> set2 = {4.7, 8.4, 3.6};

  set1 = std::move(set2);

  set1.insert(9.8);
  EXPECT_EQ(set1.size(), 4);
}

TEST(SetTest3, swap) {
  s21::Set<char> set1 = {'c', 'h', 'a', 'r'};

  set1.insert('k');

  for (const auto &i : set1) {
    std::cout << i << "\n";
  }

  s21::Set<char> set2;
  set2.swap(set1);
  std::cout << "\n";
  for (const auto &i : set2) {
    std::cout << i << "\n";
  }
}

TEST(SetTest4, CopyConstructor) {
  s21::Set<char> set1 = {'r', 'a', 'w', 'r'};
  s21::Set<char> set2(set1);

  for (const auto &i : set2) {
    std::cout << i << "\n";
  }
}

TEST(SetTest5, MoveConstructor) {
  s21::Set<char> set1 = {'h', 'e', 'l', 'l', 'o'};
  s21::Set<char> set2(std::move(set1));

  for (const auto &i : set2) {
    std::cout << i << "\n";
  }
}

TEST(SetTest6, empty) {
  s21::Set<char> set1;
  std::set<char> set2;
  EXPECT_EQ(set1.empty(), true);
  EXPECT_EQ(set2.empty(), true);

  set1.insert('5');
  set2.insert('5');
  EXPECT_EQ(set1.empty(), false);
  EXPECT_EQ(set2.empty(), false);
}

TEST(SetTest7, max_size) {
  std::set<int> set1 = {4, 2, 1, 3, 6, 7};
  s21::Set<int> test_set1 = {4, 2, 1, 3, 6, 7};

  EXPECT_EQ(set1.size(), test_set1.size());
  EXPECT_EQ(set1.max_size(), test_set1.max_size());

  std::set<int> set2;
  s21::Set<int> test_set2;
  EXPECT_EQ(set2.size(), test_set2.size());
  EXPECT_EQ(set2.max_size(), test_set2.max_size());
}

TEST(SetTest8, clear) {
  std::set<int> set1 = {4, 2, 1, 3, 6, 7};
  s21::Set<int> test_set1 = {4, 2, 1, 3, 6, 7};

  EXPECT_EQ(set1.size(), test_set1.size());

  set1.clear();
  test_set1.clear();

  EXPECT_EQ(set1.size(), test_set1.size());

  std::set<int> set2;
  s21::Set<int> test_set2;

  EXPECT_EQ(set2.size(), test_set2.size());

  set2.clear();
  test_set2.clear();

  EXPECT_EQ(set2.size(), test_set2.size());
}

TEST(SetTest9, merge) {
  std::set<int> set1 = {4, 2, 1, 3, 6, 7};
  std::set<int> set2 = {0, 9, 5};
  set1.merge(set2);

  s21::Set<int> test_set1 = {4, 2, 1, 3, 6, 7};
  s21::Set<int> test_set2 = {0, 9, 5};
  test_set1.merge(test_set2);

  EXPECT_EQ(set1.size(), test_set1.size());

  for (const auto &value : test_set1) {
    std::cout << value << "\n";
  }
}

TEST(SetTest10, find) {
  std::set<int> set1 = {4, 2, 1, 3, 6, 7};
  s21::Set<int> test_set1 = {4, 2, 1, 3, 6, 7};

  EXPECT_EQ(*set1.find(1), *test_set1.find(1));
  ASSERT_TRUE(test_set1.find(0) == nullptr);

  std::set<int> set2 = {0, 9, 5};
  s21::Set<int> test_set2 = {0, 9, 5};
  EXPECT_EQ(*set2.find(9), *test_set2.find(9));
  ASSERT_TRUE(test_set2.find(4) == nullptr);
}

TEST(SetTest11, contains) {
  s21::Set<int> test_set1 = {4, 2, 1, 3, 6, 7};

  ASSERT_TRUE(test_set1.contains(0) == false);
  ASSERT_TRUE(test_set1.contains(4) == true);
  ASSERT_TRUE(test_set1.contains(7) == true);

  s21::Set<int> test_set2 = {0, 9, 5};

  ASSERT_TRUE(test_set2.contains(4) == false);
  ASSERT_TRUE(test_set2.contains(9) == true);
  ASSERT_TRUE(test_set2.contains(5) == true);
}

TEST(SetTest12, erase) {
  std::set<int> set1 = {4, 2, 1, 3, 6, 7};
  s21::Set<int> test_set1 = {4, 2, 1, 3, 6, 7};
  EXPECT_EQ(set1.size(), test_set1.size());
  set1.erase(4);

  s21::BinaryTree<int>::Iterator i1 = test_set1.begin();
  test_set1.erase(i1);

  EXPECT_EQ(set1.size(), test_set1.size());

  ++i1;
  test_set1.erase(i1);
  ++i1;
  test_set1.erase(i1);
  ++i1;
  test_set1.erase(i1);
  ++i1;
  test_set1.erase(i1);
  ++i1;
  test_set1.erase(i1);

  EXPECT_EQ(test_set1.size(), 0);
}

TEST(SetTest13, erase) {
  std::set<int> set1 = {17};
  s21::Set<int> test_set1 = {17};
  EXPECT_EQ(set1.size(), test_set1.size());
  set1.erase(17);

  s21::BinaryTree<int>::Iterator i1 = test_set1.begin();
  test_set1.erase(i1);

  EXPECT_EQ(set1.size(), test_set1.size());

  EXPECT_EQ(test_set1.size(), 0);
}

TEST(SetTest14, EraseTest) {
  std::set<int> stdSet = {4, 2, 1, 3, 6, 7};
  s21::Set<int> testSet = {4, 2, 1, 3, 6, 7};
  EXPECT_EQ(stdSet.size(), testSet.size());

  stdSet.erase(2);
  s21::BinaryTree<int>::Iterator it = testSet.begin();
  ++it;
  testSet.erase(it);

  EXPECT_EQ(stdSet.size(), testSet.size());

  std::cout << "Remaining elements in testSet:\n";
  for (const auto &value : testSet) {
    std::cout << value << "\n";
  }

  EXPECT_EQ(testSet.size(), 5);
}

TEST(SetTest15, EraseTest) {
  std::set<int> stdSet = {4, 2, 1, 3, 6, 7};
  s21::Set<int> testSet = {4, 2, 1, 3, 6, 7};
  EXPECT_EQ(stdSet.size(), testSet.size());

  stdSet.erase(4);
  s21::BinaryTree<int>::Iterator it = testSet.begin();
  ++it;
  ++it;
  ++it;
  testSet.erase(it);

  EXPECT_EQ(stdSet.size(), testSet.size());

  std::cout << "Remaining elements in testSet:\n";
  for (const auto &value : testSet) {
    std::cout << value << "\n";
  }

  EXPECT_EQ(testSet.size(), 5);

  std::set<int> stdSet1 = {0, 9, 5};
  s21::Set<int> testSet1 = {0, 9, 5};
  EXPECT_EQ(stdSet1.size(), testSet1.size());

  stdSet1.erase(0);
  s21::BinaryTree<int>::Iterator it1 = testSet1.begin();

  testSet1.erase(it1);

  EXPECT_EQ(testSet1.size(), 2);
  ++it1;
  testSet.erase(it1);
}

TEST(SetTest16, EraseTest) {
  std::set<int> stdSet = {10, 12, 7, 9};
  s21::Set<int> testSet = {10, 12, 7, 9};
  EXPECT_EQ(stdSet.size(), testSet.size());

  stdSet.erase(9);
  s21::BinaryTree<int>::Iterator it = testSet.begin();
  ++it;
  testSet.erase(it);

  EXPECT_EQ(stdSet.size(), testSet.size());

  EXPECT_EQ(testSet.size(), 3);

  --it;
  testSet.erase(it);
  //    std::cout << "Remaining elements in testSet:\n";
  //    for (const auto &value: testSet) {
  //        std::cout << value << "\n";
  //    }
  ++it;
  testSet.erase(it);
}

TEST(SetTest17, EraseTest) {
  std::set<int> stdSet = {12, 10, 7, 9, 6};
  s21::Set<int> testSet = {12, 10, 7, 9, 6};
  EXPECT_EQ(stdSet.size(), testSet.size());

  stdSet.erase(10);
  s21::BinaryTree<int>::Iterator it = testSet.begin();
  ++it;
  ++it;
  ++it;
  testSet.erase(it);

  EXPECT_EQ(stdSet.size(), testSet.size());

  EXPECT_EQ(testSet.size(), 4);

  --it;
  --it;
  testSet.erase(it);
  //    std::cout << "Remaining elements in testSet:\n";
  //    for (const auto &value: testSet) {
  //        std::cout << value << "\n";
  //    }
}

TEST(SetTest18, EraseTest) {
  std::set<int> stdSet = {10, 6, 8, 7, 9, 4};
  s21::Set<int> testSet = {10, 6, 8, 7, 9, 4};
  EXPECT_EQ(stdSet.size(), testSet.size());

  stdSet.erase(6);
  s21::BinaryTree<int>::Iterator it = testSet.begin();
  ++it;
  testSet.erase(it);

  EXPECT_EQ(stdSet.size(), testSet.size());

  EXPECT_EQ(testSet.size(), 5);

  std::cout << "Remaining elements in testSet:\n";
  for (const auto &value : testSet) {
    std::cout << value << "\n";
  }
}

TEST(SetTest19, EraseTest) {
  std::set<int> stdSet = {10, 12, 14};
  s21::Set<int> testSet = {10, 12, 14};
  EXPECT_EQ(stdSet.size(), testSet.size());

  stdSet.erase(12);
  s21::BinaryTree<int>::Iterator it = testSet.begin();
  ++it;
  testSet.erase(it);

  EXPECT_EQ(stdSet.size(), testSet.size());

  EXPECT_EQ(testSet.size(), 2);

  std::cout << "Remaining elements in testSet:\n";
  for (const auto &value : testSet) {
    std::cout << value << "\n";
  }
}