#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_LIST_LIST_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_LIST_LIST_H

#include <iostream>
#include <limits>

namespace s21 {

template <class T>
class list {
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;

 public:
  list();
  list(const list &other);
  list(list &&other) noexcept;
  list(std::initializer_list<value_type> init);
  list(size_type n);
  ~list();
  list &operator=(list &&other) noexcept;
  list &operator=(const list &other);

  size_type max_size() const;
  size_type size() const;
  bool empty() const;

  const_reference back() const;
  const_reference front() const;
  reference front();
  reference back();

  void clear();

  void swap(list &&other) noexcept;
  void swap(list &other);

  void unique();
  void reverse();

  void merge(list &other);

  reference operator[](const size_type i);
  const_reference operator[](const size_type i) const;

  void pop_front();
  void pop_back();

  void push_front(value_type &&value);
  void push_front(const_reference &value);
  void push_back(const_reference value);
  void push_back(value_type &&value);

 private:
  struct Node {
   public:
    Node(const_reference value)
        : value_(value), next_(nullptr), prev_(nullptr) {}

    Node(T &&value) : value_(value_type()), next_(nullptr), prev_(nullptr) {
      value_ = std::move(value);
    }
    Node(const Node &node)
        : value_(node.value_), next_(node.next_), prev_(node.prev_) {}

    value_type value_;
    Node *next_;
    Node *prev_;
  };

  Node *top_;
  Node *bottom_;

 public:
  template <typename value_type>
  class IteratorList {
   public:
    IteratorList() : iter_node(nullptr) {}
    IteratorList(Node *iter) { iter_node = iter; }

    IteratorList &operator++() {
      iter_node = iter_node->next_;
      return *this;
    }

    IteratorList &operator++(int) {
      iter_node = iter_node->next_;
      return *this;
    }

    IteratorList &operator--(int) {
      iter_node = iter_node->prev_;
      return *this;
    }

    IteratorList &operator--() {
      iter_node = iter_node->prev_;
      return *this;
    }

    bool operator==(const IteratorList &other) {
      return iter_node == other.iter_node;
    }

    bool operator!=(const IteratorList &other) {
      return iter_node != other.iter_node;
    }

    reference operator*() {
      if (!iter_node) {
        throw std::out_of_range("iter_value is empty");
      }
      return iter_node->value_;
    }

    Node *iter_node;
    friend class list<T>;
  };

  template <typename value_type>
  class ConstIteratorList : public IteratorList<value_type> {
   public:
    ConstIteratorList(IteratorList<value_type> other)
        : IteratorList<value_type>(other) {}
    const_reference operator*() {
      return IteratorList<value_type>::operator*();
    }
  };

  using iterator = IteratorList<value_type>;
  using const_iterator = ConstIteratorList<value_type>;

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  iterator insert(const_iterator pos, const_reference value);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

  void erase(iterator pos);
  void splice(const_iterator pos, list &other);

  void sort();

 private:
  int distance(iterator top, iterator bottom);

  void copy(const list &other);

  void basic_constructor();

  void bind();

  void changeSize(bool flag);

  size_type size_;

  int getIndex(iterator item) const;
  int partite(int left, int right);
  iterator getByIndex(int index) const;
  void quickSort(int left, int right);

  void add_func_for_front_push(Node *node);
  void add_func_for_push_back(Node *node);
  void add_func_for_empty_push(Node *node);
  template <typename... Args>
  void add_insert_many(const_iterator pos, Args &&...args);
};

}  // namespace s21
#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_LIST_LIST_H
