#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_ITERATOR_S21_ITERATOR_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_ITERATOR_S21_ITERATOR_H

namespace s21 {
template <typename T>
class VecArrIterator {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using size_type = std::size_t;

  VecArrIterator(const VecArrIterator& iter);
  VecArrIterator(pointer value);
  VecArrIterator<value_type>& operator=(const VecArrIterator& iter);
  VecArrIterator<value_type>& operator=(VecArrIterator&& iter);

  bool operator!=(const VecArrIterator& other) const;
  bool operator==(const VecArrIterator& other) const;
  bool operator>(const VecArrIterator& other) const;
  bool operator>=(const VecArrIterator& other) const;
  bool operator<(const VecArrIterator& other) const;
  bool operator<=(const VecArrIterator& other) const;
  pointer operator->();
  reference operator*() const;
  VecArrIterator& operator++();
  VecArrIterator& operator--();
  VecArrIterator& operator++(int);
  VecArrIterator& operator--(int);
  VecArrIterator operator+(size_type value) const;
  VecArrIterator operator-(size_type value) const;
  VecArrIterator& operator+=(size_type value);
  VecArrIterator& operator-=(size_type index);
  size_type operator-(const VecArrIterator& other) const;

 private:
  pointer val;
};

template <typename T>
class VecArrConstIterator {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using const_pointer = const T*;
  using size_type = std::size_t;

  VecArrConstIterator(const VecArrConstIterator& iter);
  VecArrConstIterator(pointer value);
  VecArrConstIterator(const_pointer value);

  bool operator!=(const VecArrConstIterator& other) const;
  bool operator==(const VecArrConstIterator& other) const;
  bool operator>(const VecArrConstIterator& other) const;
  bool operator>=(const VecArrConstIterator& other) const;
  bool operator<(const VecArrConstIterator& other) const;
  bool operator<=(const VecArrConstIterator& other) const;
  pointer operator->();
  value_type operator*() const;
  VecArrConstIterator& operator++();
  VecArrConstIterator& operator--();
  VecArrConstIterator& operator++(int);
  VecArrConstIterator& operator--(int);
  VecArrConstIterator operator+(size_type value) const;
  VecArrConstIterator operator-(size_type value) const;
  VecArrConstIterator& operator+=(size_type value);
  VecArrConstIterator& operator-=(size_type index);
  size_type operator-(const VecArrConstIterator& other) const;

 private:
  const_pointer val;
};
}  // namespace s21

#include "iterator.tpp"

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_ITERATOR_S21_ITERATOR_H