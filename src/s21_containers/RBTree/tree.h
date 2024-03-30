#ifndef SRC_S21_CONTAINERS_3_SRC_S21_CONTAINERS_RBTREE_TREE_H
#define SRC_S21_CONTAINERS_3_SRC_S21_CONTAINERS_RBTREE_TREE_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

template <typename T, typename V>
class RBTree {
 protected:
  struct Node {
    T key;
    V value;
    std::pair<T, V> data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
  };
  enum NodeColor { RED, BLACK };
  typedef Node *NodePtr;

 public:
  RBTree();
  ~RBTree();
  RBTree(const RBTree &other);
  RBTree(RBTree &&other);
  void Clear();
  NodePtr MaxNode(NodePtr src);
  bool Empty();
  size_t Size();
  RBTree<T, V> &operator=(RBTree<T, V> &&other);
  RBTree<T, V> &operator=(const RBTree<T, V> &other);
  NodePtr Minimum(NodePtr node);
  NodePtr Minimum(NodePtr node) const;
  void Traverse(Node *node, size_t &count);

  class RBTreeIterator {
   public:
    RBTreeIterator();
    RBTreeIterator(NodePtr start_node, NodePtr null_node);

    T GetKey() const;

    V GetValue() const;

    NodePtr GetNode();

    bool HasNext();

    NodePtr Next();

    RBTreeIterator &operator++();

    RBTreeIterator operator++(int);

    RBTreeIterator &operator--();

    RBTreeIterator operator--(int);

    bool operator!=(const RBTreeIterator &other) const;

    T &operator*() const;

    std::pair<T, V> *operator->() const;

    bool operator==(const RBTreeIterator &other) const;

   private:
    NodePtr current;
    NodePtr tnull;
  };

  class ConstIterator {
   public:
    ConstIterator();
    ConstIterator(const NodePtr start_node, const NodePtr null_node);

    const T GetKey() const;

    const V GetValue() const;

    NodePtr GetNode() const;

    bool HasNext() const;

    NodePtr Next();

    ConstIterator &operator++();

    ConstIterator operator++(int);

    ConstIterator &operator--();

    ConstIterator operator--(int);

    bool operator!=(const ConstIterator &other) const;

    bool operator==(const ConstIterator &other) const;

    const T &operator*() const;

    const std::pair<T, V> *operator->() const;

   private:
    NodePtr current;
    NodePtr tnull;
  };

  ConstIterator cbegin() const;
  ConstIterator cend() const;
  RBTreeIterator begin();
  RBTreeIterator end();
  void Erase(RBTreeIterator pos);
  void Swap(RBTree &other);
  bool Contains(const T &key) const;
  RBTreeIterator Find(const T &key);
  size_t MaxSize();
  void Merge(RBTree &other);
  std::pair<RBTreeIterator, bool> Insert(const T &key, const V &value);
  void InsertNode(T key, V value);
  std::pair<RBTreeIterator, bool> InsertMulti(const T &key, const V &value);
  RBTreeIterator LowerBound(const T &key);
  RBTreeIterator UpperBound(const T &key);
  std::pair<RBTreeIterator, RBTreeIterator> EqualRange(const T &key);
  size_t Count(const T &key);

 protected:
  NodePtr root;
  Node *tnull;

 private:
  void Allocate();
  void ClearNode(Node *node);
  void LeftRotate(NodePtr x);
  void RightRotate(NodePtr x);
  void DeleteNode(T data);
  void DeleteFix(NodePtr x);
  void RBTransplant(NodePtr u, NodePtr v);
  void DeleteNodeHelper(NodePtr node, T key);
  void InsertFix(NodePtr k);
  NodePtr CreateNode(const T &key, const V &value);
  void AttachNode(NodePtr node, NodePtr parent);
  void FindInsertionPoint(NodePtr node, NodePtr &y, NodePtr &x);
};

#include "tree.tpp"

#endif  // SRC_S21_CONTAINERS_3_SRC_S21_CONTAINERS_RBTREE_TREE_H