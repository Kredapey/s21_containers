#include <gtest/gtest.h>

#include <set>

#include "start_test.h"

bool isEqual(s21::multiset<int> test, std::multiset<int> origin) {
  auto it_origin = origin.begin();
  for (auto it_test = test.begin(); it_test.HasNext(); it_test.Next()) {
    if (*it_test != *it_origin) return false;
    ++it_origin;
  }
  return true;
}

TEST(CONSTRUCTOR, DEFAULT) {
  s21::multiset<int> test;
  std::multiset<int> origin;
  ASSERT_EQ(isEqual(test, origin), true);
}

TEST(CONSTRUCTOR, INIT_LIST) {
  s21::multiset<int> test{1, 2, 3};
  std::multiset<int> origin{1, 2, 3};
  ASSERT_EQ(isEqual(test, origin), true);
}

TEST(CONSTRUCTOR, COPY) {
  s21::multiset<int> test{1, 2, 3};
  s21::multiset<int> test_reserve(test);
  std::multiset<int> origin{1, 2, 3};
  ASSERT_EQ(isEqual(test_reserve, origin), true);
}

TEST(CONSTRUCTOR, MOVE) {
  s21::multiset<int> test{1, 2, 3};
  s21::multiset<int> test_reserve(std::move(test));
  std::multiset<int> origin{1, 2, 3};
  ASSERT_EQ(isEqual(test_reserve, origin), true);
}

TEST(CONSTRUCTOR, OVERLOAD_EQUAL) {
  s21::multiset<int> test{1, 2, 3};
  s21::multiset<int> test_reserve = test;
  std::multiset<int> origin{1, 2, 3};
  ASSERT_EQ(isEqual(test_reserve, origin), true);
}

TEST(FUNCTION, SIZE) {
  s21::multiset<int> test{1, 2, 3};
  std::multiset<int> origin{1, 2, 3};
  ASSERT_EQ(test.size(), origin.size());
}

TEST(FUNCTION, EMPTY) {
  s21::multiset<int> test;
  std::multiset<int> origin;
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(FUNCTION, CLEAR) {
  s21::multiset<int> test{1, 2, 3};
  std::multiset<int> origin{1, 2, 3};
  test.clear();
  origin.clear();
  ASSERT_EQ(isEqual(test, origin), true);
}

TEST(FUNCTION, ERASE) {
  s21::multiset<int> test{1, 2, 3};
  std::multiset<int> origin{1, 2, 3};
  auto it_test = test.begin();
  auto it_origin = origin.begin();
  ++it_test;
  ++it_origin;
  test.erase(it_test);
  origin.erase(it_origin);
  ASSERT_EQ(isEqual(test, origin), true);
}

TEST(FUNCTION, SWAP) {
  s21::multiset<int> test{1, 2, 3};
  s21::multiset<int> test_reserve{4, 5, 6};
  std::multiset<int> origin{1, 2, 3};
  test.swap(test_reserve);
  ASSERT_EQ(isEqual(test_reserve, origin), true);
}

TEST(FUNCTION, CONTAINS) {
  s21::multiset<int> test{1, 2, 3};
  ASSERT_EQ(test.contains(3), true);
  ASSERT_EQ(test.contains(2), true);
  ASSERT_EQ(test.contains(1), true);
  ASSERT_EQ(test.contains(0), false);
}

TEST(FUNCTION, FIND) {
  s21::multiset<int> test{1, 2, 3, 4, 5};
  auto it = test.find(3);
  int counter = 0;
  while (it.HasNext()) {
    it.Next();
    counter++;
  }
  ASSERT_EQ(counter, 3);
}

TEST(FUNCTION, MERGE) {
  s21::multiset<int> test{1, 2, 3};
  s21::multiset<int> test_reserve{4, 5, 6};
  std::multiset<int> origin{1, 2, 3, 4, 5, 6};
  test.merge(test_reserve);
  ASSERT_EQ(isEqual(test, origin), true);
}

TEST(FUNCTION, MAX_SIZE) {
  s21::multiset<int> test{};
  std::multiset<int> origin{};

  ASSERT_GE(test.max_size(), origin.max_size());
}

TEST(FUNCTION, INSERT) {
  s21::multiset<int> test{1, 2, 3};
  std::multiset<int> origin{1, 2, 3, 4, 5, 6};
  test.insert(4);
  test.insert(5);
  test.insert(6);
  ASSERT_EQ(isEqual(test, origin), true);
}

TEST(FUNCTION, BEGIN) {
  s21::multiset<int> test{1, 2, 3};
  auto it = test.begin();
  int timer = 0;
  while (it.HasNext()) {
    timer++;
    it.Next();
  }
  ASSERT_EQ(timer, 3);
}

TEST(FUNCTION, END) {
  s21::multiset<int> test{1, 2, 3};
  auto it = test.end();
  int timer = 0;
  while (it.HasNext()) {
    timer++;
    it.Next();
  }
  ASSERT_EQ(timer, 0);
}

TEST(FUNCTION, COUNT) {
  s21::multiset<int> test{1, 2, 3};
  std::multiset<int> origin{1, 2, 3};
  test.insert(3);
  origin.insert(3);
  ASSERT_EQ(test.count(3), origin.count(3));
}

TEST(FUNCTION, EQUAL_RANGE) {
  s21::multiset<int> rbTree;
  std::multiset<int> stdSet;

  rbTree.insert(1);
  rbTree.insert(2);
  rbTree.insert(3);
  stdSet.insert(1);
  stdSet.insert(2);
  stdSet.insert(3);

  auto res1 = rbTree.equal_range(2);
  auto stdRes1 = stdSet.equal_range(2);
  auto ress = res1.first;
  auto stdRess = stdRes1.first;

  ASSERT_EQ(*ress, *stdRess);
}

TEST(FUNCTION, LOWER_BOUND) {
  std::multiset<int> origin{1, 2, 3, 4, 4, 4, 5, 6, 7, 8};
  s21::multiset<int> test{1, 2, 3, 4, 4, 4, 5, 6, 7, 8};
  auto it_test = test.lower_bound(4);
  auto it_origin = origin.lower_bound(4);
  ASSERT_EQ(*it_test, *it_origin);
}

TEST(FUNCTION, UPPER_BOUND) {
  std::multiset<int> origin{1, 2, 3, 4, 4, 4, 5, 6, 7, 8};
  s21::multiset<int> test{1, 2, 3, 4, 4, 4, 5, 6, 7, 8};
  auto it_test = test.upper_bound(4);
  auto it_origin = origin.upper_bound(4);
  ASSERT_EQ(*it_test, *it_origin);
}

TEST(multiset, InsertMany) {
  std::multiset<int> orig_set = {1, 2};
  s21::multiset<int> my_set = {1, 2};
  orig_set.insert(2);
  orig_set.insert(4);
  my_set.insert_many(2, 4);
  auto it = my_set.begin();
  auto it1 = orig_set.begin();
  for (; it != my_set.end(); ++it, ++it1) {
    EXPECT_EQ(*it, *it1);
  }
}
