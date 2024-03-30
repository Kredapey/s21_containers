#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_QUEUE_QUEUE_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_QUEUE_QUEUE_H

#include <iostream>

#include "../list/s21_list.h"

namespace s21 {

template <class T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &other);
  queue(queue &&other) noexcept;
  ~queue();

  const_reference front() const;
  reference front();

  const_reference back() const;
  reference back();

  bool empty() const;
  size_type size() const;
  void clear();

  void push(value_type &&value);
  void push(const value_type &value);

  void pop();

  void swap(queue &other);

  template <class... Args>
  void insert_many_back(Args &&...args);

  queue &operator=(queue &&other) noexcept;
  queue &operator=(queue &other);

  reference operator[](const size_type &i);
  const_reference operator[](const size_type &i) const;

 private:
  Container data_;
};

}  // namespace s21

#include "s21_queue.tpp"

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_QUEUE_QUEUE_H
