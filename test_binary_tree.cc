#include <gtest/gtest.h>

#include <iostream>

#include "s21_binary_tree.h"

TEST(BinaryTreeTest1, binaryTree) {
  s21::BinaryTree<int> binaryTree1({10, 7, 9, 12, 6, 14, 11, 3, 4});
  binaryTree1.PrintTreeMain();

  EXPECT_EQ(*(binaryTree1.begin()), 3);

  for (const auto &i : binaryTree1) {
    std::cout << i << "\n";
  }

  EXPECT_EQ(binaryTree1.FindNode(11)->val, 11);
}

TEST(BinaryTreeTest2, binaryTree) {
  s21::BinaryTree<int> binaryTree0({1});
  s21::BinaryTree<int> binaryTree2(binaryTree0);

  EXPECT_EQ(*(binaryTree2.begin()), 1);
}

TEST(BinaryTreeTest3, binaryTree) {
  s21::BinaryTree<int> binaryTree({1, 2, 3, 4, 5, 6, 7, 8, 9});

  s21::BinaryTree<int> binaryTree_copy(std::move(binaryTree));

  for (const auto &i : binaryTree_copy) {
    std::cout << i << "\n";
  }
}

TEST(BinaryTreeTest4, MoveAssignmentOperator) {
  s21::BinaryTree<double> binaryTree({4.5, 6.7});

  s21::BinaryTree<double> otherTree(std::move(binaryTree));

  for (const auto &i : otherTree) {
    std::cout << i << "\n";
  }

  EXPECT_EQ(otherTree.size(), 2);
}

TEST(BinaryTreeTest5, MoveAssignmentOperator) {
  s21::BinaryTree<int> binaryTree({9, 8, 7, 6, 5, 4, 3, 2, 1});

  s21::BinaryTree<int> binaryTree_copy;

  binaryTree_copy = std::move(binaryTree);

  for (const auto &i : binaryTree_copy) {
    std::cout << i << "\n";
  }

  EXPECT_EQ(binaryTree_copy.FindNode(5)->val, 5);
  ASSERT_TRUE(binaryTree_copy.FindNode(0) == nullptr);
}
