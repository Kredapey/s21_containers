#ifndef CPP2_S21_CONTAINERS_3_SRC__S21_CONTAINERS_MAP_S21_MAP_H
#define CPP2_S21_CONTAINERS_3_SRC__S21_CONTAINERS_MAP_S21_MAP_H

#include <iostream>
#include <vector>

#include "../RBTree/tree.h"

namespace s21 {
template <typename Key, typename T>
class map : public RBTree<Key, T> {
 public:
  class MapIterator;
  class ConstMapIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using reference = value_type&;
  using const_referece = const value_type&;
  using size_type = std::size_t;

  map() : RBTree<Key, T>(){};
  map(std::initializer_list<value_type> const& items);
  map(const map<key_type, mapped_type>& m) : RBTree<Key, T>(m){};
  map(map<key_type, mapped_type>&& m) : RBTree<Key, T>(std::move(m)){};
  ~map() = default;
  map<key_type, mapped_type> operator=(map<key_type, mapped_type>&& m);

  mapped_type& at(const key_type key);
  mapped_type& operator[](const key_type key);

  iterator begin();
  const_iterator cbegin();
  iterator end();
  const_iterator cend();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void erase(iterator pos);
  void swap(map<key_type, mapped_type>& other);
  void merge(map<key_type, mapped_type>& other);
  bool contains(const key_type& key);

  class MapIterator : public RBTree<Key, T>::RBTreeIterator {
    friend class map;

   public:
    MapIterator() : RBTree<Key, T>::RBTreeIterator(){};
    MapIterator(typename RBTree<Key, T>::NodePtr start_node,
                typename RBTree<Key, T>::NodePtr null_node)
        : RBTree<Key, T>::RBTreeIterator(start_node, null_node){};
    value_type& operator*();
  };

  class ConstMapIterator : public MapIterator {
    friend class map;

   public:
    ConstMapIterator(typename RBTree<Key, T>::NodePtr start_node,
                     typename RBTree<Key, T>::NodePtr null_node)
        : RBTree<Key, T>::ConstIterator(start_node, null_node){};
    value_type& operator*() const;
  };
};

}  // namespace s21

#include "s21_map.tpp"

#endif  // CPP2_S21_CONTAINERS_3_SRC__S21_CONTAINERS_MAP_S21_MAP_H