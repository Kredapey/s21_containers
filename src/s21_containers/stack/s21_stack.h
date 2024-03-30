#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_STACK_STACK_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_STACK_STACK_H

#include <iostream>

#include "../list/s21_list.h"

namespace s21 {

template <class T, class Container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &other);
  stack(stack &&other) noexcept;
  ~stack();

  const_reference top() const;
  reference top();

  bool empty() const;
  size_type size() const;
  void clear();

  void push(value_type &&value);
  void push(const value_type &value);

  void pop();

  void swap(stack &other);

  template <typename... Args>
  void insert_many_front(Args &&...args);

  stack &operator=(stack &&other) noexcept;
  stack &operator=(stack &other);

  reference operator[](const size_type index);
  const_reference operator[](const size_type index) const;

 private:
  Container data_;
};
}  // namespace s21

#include "s21_stack.tpp"
#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_STACK_STACK_H
