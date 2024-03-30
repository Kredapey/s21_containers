#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_VECTOR_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_VECTOR_S21_VECTOR_H

#include <cmath>
#include <iostream>

namespace s21 {
template <typename T>
class VecArrIterator;

template <typename T>
class VecArrConstIterator;

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VecArrIterator<T>;
  using const_iterator = VecArrConstIterator<T>;
  using size_type = std::size_t;
  using pointer = T*;

  // Vector Member functions
  vector();
  vector(size_type size_vec);
  vector(const vector<value_type>& other);
  vector(vector<value_type>&& other) noexcept;
  vector(std::initializer_list<value_type> other);
  ~vector();
  vector<value_type>& operator=(vector<value_type>&& other) noexcept;

  // Vector Element access
  reference at(size_type place) const;  // Не уверен по поводу конст
  reference operator[](size_type i) const;
  const_reference front() const;
  const_reference back() const;
  pointer data();

  // Vector Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Vector Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type count);
  size_type capacity() const;
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(value_type new_value);
  void pop_back();
  void swap(vector<value_type>& other);

  // Доп часть
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  pointer arr;  // Массив, в котором хранятся элементы
  size_type m_size;      // Размер массива
  size_type m_capacity;  // Размер выделенной памяти

  // Вспомогательные функции
  void change_capacity();
  void free_vector();
  void copy_vector(const vector<value_type>& other);
  void init_list_copy(std::initializer_list<value_type> other);
};
}  // namespace s21

#include "../iterator/iterator.h"
#include "s21_vector.tpp"

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_VECTOR_S21_VECTOR_H