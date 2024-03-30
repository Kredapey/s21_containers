#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_SET_SET_H_
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_SET_SET_H_

#include "../RBTree/tree.h"

namespace s21 {
template <typename T>
class set {
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

  set() {}

  set(std::initializer_list<T> const &items) {
    for (const T &item : items)
      if (!rbtree.Contains(item)) rbtree.InsertNode(item, item);
  }

  set(const set &other) : rbtree(other.rbtree) {}

  set(set &&other) : rbtree(std::move(other.rbtree)) {}

  ~set() {}

  set &operator=(set &&other) {
    if (this != &other) rbtree = std::move(other.rbtree);
    return *this;
  }

  size_type size() { return rbtree.Size(); }

  bool empty() { return rbtree.Empty(); }

  void clear() { rbtree.Clear(); }

  void erase(iterator pos) { rbtree.Erase(pos); }

  void swap(set &other) { rbtree.Swap(other.rbtree); }

  bool contains(const T &key) { return rbtree.Contains(key); }

  iterator find(const T &key) { return rbtree.Find(key); }

  void merge(set &other) { rbtree.Merge(other.rbtree); };

  size_type max_size() { return rbtree.MaxSize(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return rbtree.Insert(value, value);
  }

  iterator begin() { return rbtree.begin(); }

  iterator end() { return rbtree.end(); }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    for (const auto &a : {args...}) res.push_back(insert(a));
    return res;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_SET_SET_H_
