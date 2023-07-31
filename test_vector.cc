#include <gtest/gtest.h>

#include <vector>

#include "s21_vector.h"
using namespace s21;

TEST(VectorConstructorTest, DefaultConstructor) {
  Vector<int> v;

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);

  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorConstructorTest, DefaultConstructorWithData) {
  Vector<int> v;

  v.push_back(10);
  v.push_back(20);
  v.push_back(30);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);

  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
}

TEST(VectorConstructorTest, SizeConstructor) {
  Vector<int> v(5);

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorConstructorTest, InitializerListConstructor) {
  Vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], i + 1);
  }
}

TEST(VectorConstructorTest, EmptyInitializerListConstructor) {
  Vector<int> v = {};

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorConstructorTest, CopyConstructor) {
  Vector<int> v1 = {1, 2, 3, 4, 5};

  Vector<int> v2(v1);

  EXPECT_EQ(v2.size(), v1.size());
  EXPECT_EQ(v2.capacity(), v1.capacity());

  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorConstructorTest, EmptyCopyConstructor) {
  Vector<int> v1;

  Vector<int> v2(v1);

  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.capacity(), 0);
}

TEST(VectorConstructorTest, MoveConstructor) {
  Vector<int> v1 = {1, 2, 3, 4, 5};

  Vector<int> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 5);
  EXPECT_EQ(v2.capacity(), 5);

  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }

  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
  EXPECT_EQ(v1.data(), nullptr);
}

TEST(VectorConstructorTest, EmptyMoveConstructor) {
  Vector<int> v1;

  Vector<int> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.capacity(), 0);

  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
  EXPECT_EQ(v1.data(), nullptr);
}

TEST(VectorDestructorTest, NonEmptyVector) {
  Vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_NO_THROW({ v.~Vector(); });

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);

  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorDestructorTest, EmptyVector) {
  Vector<int> v;

  EXPECT_NO_THROW({ v.~Vector(); });

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);

  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorMoveAssignmentTest, MoveEmptyVector) {
  Vector<int> src;

  Vector<int> dest;
  dest = std::move(src);

  EXPECT_EQ(src.size(), 0);
  EXPECT_EQ(src.capacity(), 0);
  EXPECT_EQ(src.data(), nullptr);

  EXPECT_EQ(dest.size(), 0);
  EXPECT_EQ(dest.capacity(), 0);
  EXPECT_EQ(dest.data(), nullptr);
}

TEST(VectorMoveAssignmentTest, MoveNonEmptyVector) {
  Vector<int> src = {1, 2, 3, 4, 5};

  Vector<int> dest;
  dest = std::move(src);

  EXPECT_EQ(src.size(), 0);
  EXPECT_EQ(src.capacity(), 0);
  EXPECT_EQ(src.data(), nullptr);

  EXPECT_EQ(dest.size(), 5);
  EXPECT_GE(dest.capacity(), 5);
  EXPECT_NE(dest.data(), nullptr);
  EXPECT_EQ(dest[0], 1);
  EXPECT_EQ(dest[1], 2);
  EXPECT_EQ(dest[2], 3);
  EXPECT_EQ(dest[3], 4);
  EXPECT_EQ(dest[4], 5);
}

TEST(VectorMaxSizeTest, MaxSizeCheck) {
  Vector<int> v;

  EXPECT_EQ(v.max_size(), std::numeric_limits<Vector<int>::size_type>::max() /
                              sizeof(int) / 2u);
}

TEST(VectorReserveTest, IncreaseCapacity) {
  Vector<int> v;

  v.reserve(10);

  EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorReserveTest, IncreaseCapacityFromNonEmptyVector) {
  Vector<int> v = {1, 2, 3};

  v.reserve(10);

  EXPECT_EQ(v.capacity(), 10);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorReserveTest, DecreaseCapacity) {
  Vector<int> v = {1, 2, 3, 4, 5};

  v.reserve(3);

  EXPECT_EQ(v.capacity(), 5);

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorCapacityTest, EmptyVector) {
  Vector<int> v;

  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorCapacityTest, NonEmptyVector) {
  Vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorShrinkToFitTest, ShrinkNonEmptyVector) {
  Vector<int> v = {1, 2, 3, 4, 5};

  v.shrink_to_fit();

  EXPECT_EQ(v.capacity(), v.size());
}

TEST(VectorShrinkToFitTest, ShrinkEmptyVector) {
  Vector<int> v;

  v.shrink_to_fit();

  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorClearTest, ClearEmptyVector) {
  Vector<int> v;

  v.clear();

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, InsertIntoEmptyVector) {
  Vector<int> vec;
  vec.insert(vec.begin(), 5);

  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec[0], 5);
}

TEST(VectorTest, InsertIntoMiddle) {
  Vector<int> vec = {1, 2, 3, 4};
  vec.insert(vec.begin() + 2, 10);

  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 10);
  ASSERT_EQ(vec[3], 3);
  ASSERT_EQ(vec[4], 4);
}

TEST(VectorTest, InsertAtEnd) {
  Vector<int> vec = {1, 2, 3};
  vec.insert(vec.end(), 4);

  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
}

TEST(VectorTest, InsertReturnIterator) {
  Vector<int> vec = {1, 2, 3};
  Vector<int>::iterator it = vec.insert(vec.begin() + 1, 10);

  ASSERT_EQ(*it, 10);
}

TEST(VectorTest, InsertComparisonWithStdVector) {
  Vector<int> vec = {1, 2, 3};
  std::vector<int> stdVec = {1, 2, 3};

  vec.insert(vec.begin() + 1, 10);
  stdVec.insert(stdVec.begin() + 1, 10);

  ASSERT_EQ(vec.size(), stdVec.size());

  for (size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(vec[i], stdVec[i]);
  }
}

TEST(VectorEraseTest, EraseFromNonEmptyVector) {
  Vector<int> v = {1, 2, 3, 4, 5};

  auto it = v.begin() + 2;
  v.erase(it);

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 4);
  EXPECT_EQ(v[3], 5);
}

TEST(VectorEraseTest, EraseFromEmptyVector) {
  Vector<int> v;

  auto it = v.begin();
  v.erase(it);

  EXPECT_EQ(v.size(), 0);
}

TEST(VectorEraseTest, EraseOutOfRange) {
  Vector<int> v = {1, 2, 3};

  auto it = v.end();
  v.erase(it);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorPushBackTest, PushEmptyVector) {
  Vector<int> v;

  v.push_back(10);

  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 10);
}

TEST(VectorPushBackTest, PushNonEmptyVector) {
  Vector<int> v = {1, 2, 3};

  v.push_back(4);

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorPushBackTest, PushVectorWithCapacity) {
  Vector<int> v;
  v.reserve(10);

  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }

  EXPECT_EQ(v.size(), 10);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v[i], i);
  }
}

TEST(VectorPopBackTest, PopEmptyVector) {
  Vector<int> v;

  v.pop_back();

  EXPECT_EQ(v.size(), 0);
}

TEST(VectorPopBackTest, PopNonEmptyVector) {
  Vector<int> v = {1, 2, 3, 4};

  v.pop_back();

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorSwapTest, SwapEmptyVectors) {
  Vector<int> v1;
  Vector<int> v2;

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.capacity(), 0);
  EXPECT_EQ(v1.data(), nullptr);

  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.capacity(), 0);
  EXPECT_EQ(v2.data(), nullptr);
}

TEST(VectorSwapTest, SwapNonEmptyVectors) {
  Vector<int> v1 = {1, 2, 3};
  Vector<int> v2 = {4, 5, 6, 7};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v1.capacity(), 4);
  EXPECT_NE(v1.data(), nullptr);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);
  EXPECT_EQ(v1[3], 7);

  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2.capacity(), 3);
  EXPECT_NE(v2.data(), nullptr);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
}
