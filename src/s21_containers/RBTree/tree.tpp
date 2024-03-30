#include "tree.h"

template <typename T, typename V>
void RBTree<T, V>::Allocate() {
  tnull = new Node;
  tnull->color = RED;
  tnull->left = nullptr;
  tnull->right = nullptr;
  root = tnull;
}

template <typename T, typename V>
void RBTree<T, V>::ClearNode(Node *node) {
  if (node != tnull) {
    ClearNode(node->left);
    ClearNode(node->right);
    delete node;
  }
}

template <typename T, typename V>
void RBTree<T, V>::Traverse(Node *node, size_t &count) {
  if (node != tnull) {
    Traverse(node->left, count);
    count++;
    Traverse(node->right, count);
  }
}

template <typename T, typename V>
typename RBTree<T, V>::NodePtr RBTree<T, V>::Minimum(NodePtr node) {
  if (node == tnull) return node;
  while (node->left != tnull) node = node->left;
  return node;
}

template <typename T, typename V>
typename RBTree<T, V>::NodePtr RBTree<T, V>::Minimum(NodePtr node) const {
  if (node == tnull) return node;
  while (node->left != tnull) node = node->left;
  return node;
}

template <typename T, typename V>
void RBTree<T, V>::LeftRotate(NodePtr x) {
  NodePtr y = x->right;
  x->right = y->left;
  if (y->left != tnull) y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    this->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

template <typename T, typename V>
void RBTree<T, V>::RightRotate(NodePtr x) {
  NodePtr y = x->left;
  x->left = y->right;
  if (y->right != tnull) y->right->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    this->root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;
  y->right = x;
  x->parent = y;
}

template <typename T, typename V>
void RBTree<T, V>::DeleteNode(T data) {
  DeleteNodeHelper(this->root, data);
}

template <typename T, typename V>
void RBTree<T, V>::DeleteFix(NodePtr x) {
  NodePtr s;
  while (x != root && x->color == RED) {
    if (x == x->parent->left) {
      s = x->parent->right;
      if (s->color == BLACK) {
        s->color = RED;
        x->parent->color = BLACK;
        LeftRotate(x->parent);
        s = x->parent->right;
      }

      if (s->left->color == RED && s->right->color == RED) {
        s->color = BLACK;
        x = x->parent;
      } else {
        if (s->right->color == RED) {
          s->left->color = RED;
          s->color = BLACK;
          RightRotate(s);
          s = x->parent->right;
        }
        s->color = x->parent->color;
        x->parent->color = RED;
        s->right->color = RED;
        LeftRotate(x->parent);
        x = root;
      }
    } else {
      s = x->parent->left;
      if (s == tnull) {
      }
      if (s->color == BLACK) {
        s->color = RED;
        x->parent->color = BLACK;
        RightRotate(x->parent);
        s = x->parent->left;
      }
      if (s->right->color == RED) {
        s->color = BLACK;
        x = x->parent;
      } else {
        s->color = x->parent->color;
        x->parent->color = RED;
        s->left->color = RED;
        RightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = RED;
}

template <typename T, typename V>
void RBTree<T, V>::RBTransplant(NodePtr u, NodePtr v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}

template <typename T, typename V>
void RBTree<T, V>::DeleteNodeHelper(NodePtr node, T key) {
  NodePtr z = tnull;
  NodePtr x, y;
  while (node != tnull) {
    if (node->key == key) z = node;
    if (node->key <= key)
      node = node->right;
    else
      node = node->left;
  }
  if (z == tnull) return;
  y = z;
  int y_original_color = y->color;
  if (z->left == tnull) {
    x = z->right;
    RBTransplant(z, z->right);
  } else if (z->right == tnull) {
    x = z->left;
    RBTransplant(z, z->left);
  } else {
    y = Minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      RBTransplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    RBTransplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (z != nullptr) delete z;
  if (y_original_color == RED) DeleteFix(x);
}

template <typename T, typename V>
void RBTree<T, V>::InsertFix(NodePtr k) {
  NodePtr u;
  while (k->parent->color == BLACK) {
    if (k->parent == k->parent->parent->right) {
      u = k->parent->parent->left;
      if (u->color == BLACK) {
        u->color = RED;
        k->parent->color = RED;
        k->parent->parent->color = BLACK;
        k = k->parent->parent;
      } else {
        if (k == k->parent->left) {
          k = k->parent;
          RightRotate(k);
        }
        k->parent->color = RED;
        k->parent->parent->color = BLACK;
        LeftRotate(k->parent->parent);
      }
    } else {
      u = k->parent->parent->right;
      if (u->color == BLACK) {
        u->color = RED;
        k->parent->color = RED;
        k->parent->parent->color = BLACK;
        k = k->parent->parent;
      } else {
        k->parent->color = RED;
        k->parent->parent->color = BLACK;
        RightRotate(k->parent->parent);
      }
    }
    if (k == root) break;
  }
  root->color = RED;
}

template <typename T, typename V>
RBTree<T, V> &RBTree<T, V>::operator=(RBTree &&other) {
  if (this != &other) {
    Clear();
    root = other.root;
    tnull = other.tnull;
    other.root = nullptr;
    other.tnull = nullptr;
  }
  return *this;
}

template <typename T, typename V>
RBTree<T, V> &RBTree<T, V>::operator=(const RBTree &other) {
  Clear();
  for (auto it = other.cbegin(); it.HasNext(); it.Next()) {
    InsertNode(it.GetKey(), it.GetValue());
  }
  return *this;
}

template <typename T, typename V>
typename RBTree<T, V>::NodePtr RBTree<T, V>::CreateNode(const T &key,
                                                        const V &value) {
  NodePtr node = new Node;
  node->key = key;
  node->value = value;
  node->data = std::make_pair(node->key, node->value);
  node->parent = nullptr;
  node->left = tnull;
  node->right = tnull;
  node->color = RED;
  return node;
}

template <typename T, typename V>
void RBTree<T, V>::AttachNode(NodePtr node, NodePtr parent) {
  node->parent = parent;
  if (parent == nullptr)
    root = node;
  else if (node->key < parent->key)
    parent->left = node;
  else
    parent->right = node;
}

template <typename T, typename V>
void RBTree<T, V>::FindInsertionPoint(NodePtr node, NodePtr &y, NodePtr &x) {
  x = this->root;
  while (x != tnull) {
    y = x;
    if (node->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
}

template <typename T, typename V>
RBTree<T, V>::RBTree() {
  Allocate();
}

template <typename T, typename V>
RBTree<T, V>::RBTree(const RBTree &other) {
  Allocate();
  for (auto it = other.cbegin(); it.HasNext(); it.Next()) {
    InsertNode(it.GetKey(), it.GetValue());
  }
}

template <typename T, typename V>
RBTree<T, V>::RBTree(RBTree &&other) {
  root = other.root;
  tnull = other.tnull;

  other.root = nullptr;
  other.tnull = nullptr;
}

template <typename T, typename V>
RBTree<T, V>::~RBTree() {
  Clear();
}

template <typename T, typename V>
void RBTree<T, V>::Clear() {
  ClearNode(root);
  delete tnull;
  root = nullptr;
  tnull = nullptr;
}

template <typename T, typename V>
typename RBTree<T, V>::NodePtr RBTree<T, V>::MaxNode(NodePtr src) {
  if (src == tnull || src == nullptr) {
    return nullptr;
  }
  if (src->right == nullptr || src->right == tnull) {
    return root;
  }
  return MaxNode(src->right);
}

template <typename T, typename V>
bool RBTree<T, V>::Empty() {
  return root == tnull;
}

template <typename T, typename V>
size_t RBTree<T, V>::Size() {
  size_t count = 0;
  Traverse(root, count);
  return count;
}

template <typename T, typename V>
RBTree<T, V>::RBTreeIterator::RBTreeIterator()
    : current(nullptr), tnull(nullptr) {}

template <typename T, typename V>
RBTree<T, V>::RBTreeIterator::RBTreeIterator(NodePtr start_node,
                                             NodePtr null_node) {
  current = start_node;
  tnull = null_node;
}

template <typename T, typename V>
T RBTree<T, V>::RBTreeIterator::GetKey() const {
  return current->key;
}

template <typename T, typename V>
V RBTree<T, V>::RBTreeIterator::GetValue() const {
  return current->value;
}

template <typename T, typename V>
typename RBTree<T, V>::NodePtr RBTree<T, V>::RBTreeIterator::GetNode() {
  return current;
}

template <typename T, typename V>
bool RBTree<T, V>::RBTreeIterator::HasNext() {
  return (current != nullptr && current != tnull);
}

template <typename T, typename V>
typename RBTree<T, V>::NodePtr RBTree<T, V>::RBTreeIterator::Next() {
  NodePtr ret_val = current;
  if (current->right != tnull) {
    current = current->right;
    while (current->left != tnull) current = current->left;
  } else {
    NodePtr p = current->parent;
    while (p != nullptr && current == p->right) {
      current = p;
      p = p->parent;
    }
    current = p;
  }
  return ret_val;
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator &
RBTree<T, V>::RBTreeIterator::operator++() {
  if (current->right != tnull) {
    current = current->right;
    while (current->left != tnull) current = current->left;
  } else {
    NodePtr p = current->parent;
    while (p != nullptr && current == p->right) {
      current = p;
      p = p->parent;
    }
    current = p;
  }
  return *this;
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator RBTree<T, V>::RBTreeIterator::operator++(
    int) {
  RBTreeIterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T, typename V>
bool RBTree<T, V>::RBTreeIterator::operator!=(
    const RBTreeIterator &other) const {
  return current != other.current;
}

template <typename T, typename V>
bool RBTree<T, V>::RBTreeIterator::operator==(
    const RBTreeIterator &other) const {
  return current == other.current;
}

template <typename T, typename V>
T &RBTree<T, V>::RBTreeIterator::operator*() const {
  if (current == nullptr) {
    static T res{};
    return res;
  }
  return current->key;
}

template <typename T, typename V>
std::pair<T, V> *RBTree<T, V>::RBTreeIterator::operator->() const {
  return &(current->data);
}

template <typename T, typename V>
RBTree<T, V>::ConstIterator::ConstIterator()
    : current(nullptr), tnull(nullptr) {}

template <typename T, typename V>
RBTree<T, V>::ConstIterator::ConstIterator(
    const RBTree<T, V>::NodePtr start_node,
    const RBTree<T, V>::NodePtr null_node) {
  current = start_node;
  tnull = null_node;
}

template <typename T, typename V>
const T RBTree<T, V>::ConstIterator::GetKey() const {
  return current->key;
}

template <typename T, typename V>
const V RBTree<T, V>::ConstIterator::GetValue() const {
  return current->value;
}

template <typename T, typename V>
typename RBTree<T, V>::NodePtr RBTree<T, V>::ConstIterator::GetNode() const {
  return current;
}

template <typename T, typename V>
bool RBTree<T, V>::ConstIterator::HasNext() const {
  return (current != nullptr && current != tnull);
}

template <typename T, typename V>
typename RBTree<T, V>::NodePtr RBTree<T, V>::ConstIterator::Next() {
  NodePtr ret_val = current;
  if (current->right != tnull) {
    current = current->right;
    while (current->left != tnull) current = current->left;
  } else {
    NodePtr p = current->parent;
    while (p != nullptr && current == p->right) {
      current = p;
      p = p->parent;
    }
    current = p;
  }
  return ret_val;
}

template <typename T, typename V>
typename RBTree<T, V>::ConstIterator &
RBTree<T, V>::ConstIterator::operator++() {
  if (current->right != tnull) {
    current = current->right;
    while (current->left != tnull) current = current->left;
  } else {
    NodePtr p = current->parent;
    while (p != nullptr && current == p->right) {
      current = p;
      p = p->parent;
    }
    current = p;
  }
  return *this;
}

template <typename T, typename V>
typename RBTree<T, V>::ConstIterator RBTree<T, V>::ConstIterator::operator++(
    int) {
  RBTreeIterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T, typename V>
bool RBTree<T, V>::ConstIterator::operator!=(
    const RBTree<T, V>::ConstIterator &other) const {
  return current != other.current;
}

template <typename T, typename V>
bool RBTree<T, V>::ConstIterator::operator==(
    const RBTree<T, V>::ConstIterator &other) const {
  return current == other.current;
}

template <typename T, typename V>
const T &RBTree<T, V>::ConstIterator::operator*() const {
  if (current == nullptr) {
    static T res{};
    return res;
  }
  return current->key;
}

template <typename T, typename V>
const std::pair<T, V> *RBTree<T, V>::ConstIterator::operator->() const {
  return &(current->data);
}

template <typename T, typename V>
typename RBTree<T, V>::ConstIterator RBTree<T, V>::cbegin() const {
  return ConstIterator(Minimum(root), tnull);
}

template <typename T, typename V>
typename RBTree<T, V>::ConstIterator RBTree<T, V>::cend() const {
  ConstIterator it = cbegin();
  if (it.HasNext())
    while (it.HasNext()) it.Next();
  return it;
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator RBTree<T, V>::begin() {
  return RBTreeIterator(Minimum(root), tnull);
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator RBTree<T, V>::end() {
  RBTreeIterator it = begin();
  if (it.HasNext())
    while (it.HasNext()) it.Next();
  return it;
}

template <typename T, typename V>
size_t RBTree<T, V>::MaxSize() {
  return std::numeric_limits<size_t>::max() / 10;
}

template <typename T, typename V>
bool RBTree<T, V>::Contains(const T &key) const {
  Node *current = root;
  while (current != tnull) {
    if (current->key == key) return true;
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return false;
}

template <typename T, typename V>
void RBTree<T, V>::Swap(RBTree &other) {
  std::swap(root, other.root);
  std::swap(tnull, other.tnull);
}

template <typename T, typename V>
void RBTree<T, V>::Erase(RBTreeIterator pos) {
  Node *node = pos.GetNode();
  if (node == tnull || node == nullptr) return;
  DeleteNode(node->key);
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator RBTree<T, V>::Find(const T &key) {
  NodePtr current = root;
  while (current != tnull) {
    if (current->key == key) return RBTreeIterator(current, tnull);
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return end();
}

template <typename T, typename V>
void RBTree<T, V>::Merge(RBTree &other) {
  RBTree copy_tree(other);
  RBTree mergedTree;
  for (auto it = this->begin(); it.HasNext(); it.Next()) {
    mergedTree.Insert(it.GetKey(), it.GetValue());
  }
  for (auto it = copy_tree.begin(); it.HasNext(); it.Next()) {
    std::pair<RBTreeIterator, bool> tmp =
        mergedTree.Insert(it.GetKey(), it.GetValue());
    if (tmp.second) {
      other.Erase(tmp.first);
    }
  }
  *this = std::move(mergedTree);
}

template <typename T, typename V>
std::pair<typename RBTree<T, V>::RBTreeIterator, bool> RBTree<T, V>::Insert(
    const T &key, const V &value) {
  if (Contains(key)) {
    RBTreeIterator it = Find(key);
    return {it, false};
  }
  NodePtr node = CreateNode(key, value);
  node->color = BLACK;
  NodePtr y = nullptr;
  NodePtr x = this->root;
  FindInsertionPoint(node, y, x);
  AttachNode(node, y);
  RBTreeIterator it(node, tnull);
  if (node->parent == nullptr) {
    node->color = RED;
    return std::make_pair(it, true);
  }
  if (node->parent->parent == nullptr) return std::make_pair(it, true);
  InsertFix(node);
  return std::make_pair(it, true);
}

template <typename T, typename V>
void RBTree<T, V>::InsertNode(T key, V value) {
  NodePtr node = CreateNode(key, value);
  node->color = BLACK;
  NodePtr y = nullptr;
  NodePtr x = this->root;
  FindInsertionPoint(node, y, x);
  AttachNode(node, y);
  if (node->parent == nullptr) {
    node->color = RED;
    return;
  }
  if (node->parent->parent == nullptr) return;
  InsertFix(node);
}

template <typename T, typename V>
size_t RBTree<T, V>::Count(const T &key) {
  size_t cnt = 0;
  Node *current = root;
  while (current != tnull) {
    if (current->key == key) cnt++;
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return cnt;
}

template <typename T, typename V>
std::pair<typename RBTree<T, V>::RBTreeIterator,
          typename RBTree<T, V>::RBTreeIterator>
RBTree<T, V>::EqualRange(const T &key) {
  Node *lower = nullptr;
  Node *upper = nullptr;
  Node *current = root;

  while (current != tnull) {
    if (current->key < key) {
      current = current->right;
    } else if (key < current->key) {
      upper = current;
      current = current->left;
    } else {
      lower = current;
      break;
    }
  }

  return std::make_pair(RBTreeIterator(lower, tnull),
                        RBTreeIterator(upper, tnull));
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator RBTree<T, V>::LowerBound(const T &key) {
  Node *y = nullptr;
  Node *x = root;

  while (x != tnull) {
    if (!(x->key < key)) {
      y = x;
      x = x->left;
    } else
      x = x->right;
  }

  RBTreeIterator it(y, tnull);
  return it;
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator RBTree<T, V>::UpperBound(const T &key) {
  Node *y = nullptr;
  Node *x = root;

  while (x != tnull) {
    if (key < x->key) {
      y = x;
      x = x->left;
    } else
      x = x->right;
  }

  RBTreeIterator it(y, tnull);
  return it;
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator &
RBTree<T, V>::RBTreeIterator::operator--() {
  if (current->left != tnull) {
    current = current->left;
    while (current->right != tnull) {
      current = current->right;
    }
  } else {
    NodePtr p = current->parent;
    while (p != nullptr && current == p->left) {
      current = p;
      p = p->parent;
    }
    current = p;
  }
  return *this;
}

template <typename T, typename V>
typename RBTree<T, V>::RBTreeIterator RBTree<T, V>::RBTreeIterator::operator--(
    int) {
  RBTreeIterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T, typename V>
typename RBTree<T, V>::ConstIterator &
RBTree<T, V>::ConstIterator::operator--() {
  if (current->left != tnull) {
    current = current->left;
    while (current->right != tnull) {
      current = current->right;
    }
  } else {
    NodePtr p = current->parent;
    while (p != nullptr && current == p->left) {
      current = p;
      p = p->parent;
    }
    current = p;
  }
  return *this;
}

template <typename T, typename V>
typename RBTree<T, V>::ConstIterator RBTree<T, V>::ConstIterator::operator--(
    int) {
  RBTreeIterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T, typename V>
std::pair<typename RBTree<T, V>::RBTreeIterator, bool>
RBTree<T, V>::InsertMulti(const T &key, const V &value) {
  NodePtr node = CreateNode(key, value);
  node->color = BLACK;
  NodePtr y = nullptr;
  NodePtr x = this->root;
  FindInsertionPoint(node, y, x);
  AttachNode(node, y);
  RBTreeIterator it(node, tnull);
  if (node->parent == nullptr) {
    node->color = RED;
    return std::make_pair(it, true);
  }
  if (node->parent->parent == nullptr) return std::make_pair(it, true);
  ;
  InsertFix(node);
  return std::make_pair(it, true);
}
