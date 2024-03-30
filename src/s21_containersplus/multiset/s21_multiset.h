#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERSPLUS_MULTISET_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERSPLUS_MULTISET_S21_MULTISET_H_

#include "../../s21_containers/RBTree/tree.h"

namespace s21 {
template <typename T>
class multiset {
 private:
  RBTree<T, T> rbtree;

 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename RBTree<T, T>::RBTreeIterator;
  using const_iterator = typename RBTree<T, T>::ConstIterator;

  multiset() {}

  multiset(std::initializer_list<T> const &items) {
    for (const T &item : items) rbtree.InsertNode(item, item);
  }

  multiset(const multiset &ms) : rbtree(ms.rbtree) {}

  multiset(multiset &&ms) : rbtree(std::move(ms.rbtree)) {}

  ~multiset() {}

  multiset &operator=(multiset &&ms) {
    if (this != &ms) rbtree = std::move(ms.rbtree);
    return *this;
  }

  size_type size() { return rbtree.Size(); }

  bool empty() { return rbtree.Empty(); }

  void clear() { rbtree.Clear(); }

  void erase(iterator pos) { rbtree.Erase(pos); }

  void swap(multiset &other) { rbtree.Swap(other.rbtree); }

  bool contains(const T &key) { return rbtree.Contains(key); }

  iterator find(const T &key) { return rbtree.Find(key); }

  void merge(multiset &other) { rbtree.Merge(other.rbtree); }

  size_type max_size() { return rbtree.MaxSize(); }

  iterator insert(const value_type &value) {
    std::pair<iterator, bool> name = rbtree.InsertMulti(value, value);
    return name.first;
  }

  iterator begin() { return rbtree.begin(); }

  iterator end() { return rbtree.end(); }

  size_type count(const T &key) { return rbtree.Count(key); }

  std::pair<iterator, iterator> equal_range(const T &key) {
    return rbtree.EqualRange(key);
  }

  iterator lower_bound(const T &key) { return rbtree.LowerBound(key); }

  iterator upper_bound(const T &key) { return rbtree.UpperBound(key); }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    for (const auto &a : {args...}) res.push_back(rbtree.InsertMulti(a, a));
    return res;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERSPLUS_MULTISET_S21_MULTISET_H_
