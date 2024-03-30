#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H

#include <cstring>
#include <iostream>

#include "../../s21_containers/iterator/iterator.h"

namespace s21 {

template <typename T>
class VecArrIterator;

template <typename T>
class VecArrConstIterator;

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using size_type = std::size_t;
  using iterator = VecArrIterator<T>;
  using const_iterator = VecArrConstIterator<T>;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array<value_type, N> &a);
  array(array<value_type, N> &&a);
  ~array() = default;
  array<value_type, N> &operator=(array<value_type, N> &&a);
  array<value_type, N> &operator=(const array<value_type, N> &a);

  reference at(size_type index);
  const_reference at(size_type index) const;
  reference operator[](size_type index);
  const_reference operator[](size_type index) const;
  const_reference front() const;
  const_reference back() const;
  pointer data();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(array<value_type, N> &other);
  void fill(const_reference value);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

 private:
  value_type arr[N] = {};
  size_type m_size;
};
}  // namespace s21

#include "s21_array.tpp"

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERSPLUS_ARRAY_S21_ARRAY_H