#include <stdexcept>
namespace s21 {
template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(
    std::initializer_list<value_type> const& items) {
  for (const value_type& item : items) {
    RBTree<key_type, mapped_type>::InsertNode(item.first, item.second);
  }
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type> map<key_type, mapped_type>::operator=(
    map<key_type, mapped_type>&& m) {
  if (this != &m) {
    RBTree<key_type, mapped_type>::operator=(std::move(m));
  }
  return *this;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::mapped_type&
map<key_type, mapped_type>::at(const key_type key) {
  typename RBTree<key_type, mapped_type>::RBTreeIterator it =
      RBTree<key_type, mapped_type>::Find(key);
  if (it == RBTree<key_type, mapped_type>::end()) {
    throw std::out_of_range("there is no element with this key");
  }
  return it->second;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::mapped_type&
map<key_type, mapped_type>::operator[](const key_type key) {
  auto it = RBTree<key_type, mapped_type>::Find(key);
  if (it == end()) {
    auto in = insert(std::make_pair(key, mapped_type{}));
    it = in.first;
  }
  return it->second;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
  return MapIterator(RBTree<key_type, mapped_type>::Minimum(this->root),
                     this->tnull);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
  if (RBTree<key_type, mapped_type>::root == nullptr ||
      RBTree<key_type, mapped_type>::root ==
          RBTree<key_type, mapped_type>::tnull) {
    return begin();
  }
  typename RBTree<key_type, mapped_type>::NodePtr last =
      RBTree<key_type, mapped_type>::MaxNode(this->root);
  MapIterator res(nullptr, last);
  return res;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::const_iterator
map<key_type, mapped_type>::cbegin() {
  return ConstMapIterator(RBTree<key_type, mapped_type>::Minimum(this->root),
                          this->tnull);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::const_iterator
map<key_type, mapped_type>::cend() {
  typename RBTree<key_type, mapped_type>::NodePtr last =
      RBTree<key_type, mapped_type>::MaxNode(this->root);
  ConstMapIterator res(nullptr, last);
  return res;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::empty() {
  return RBTree<key_type, mapped_type>::Empty();
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::size() {
  return RBTree<key_type, mapped_type>::Size();
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::max_size() {
  return RBTree<key_type, mapped_type>::MaxSize();
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
  return RBTree<key_type, mapped_type>::Clear();
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const value_type& value) {
  return insert(value.first, value.second);
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
  std::pair<iterator, bool> res_val{};
  std::pair<typename RBTree<key_type, mapped_type>::RBTreeIterator, bool> tmp =
      RBTree<key_type, mapped_type>::Insert(key, obj);
  res_val.second = tmp.second;
  typename RBTree<key_type, mapped_type>::RBTreeIterator tree_it = tmp.first;
  typename RBTree<key_type, mapped_type>::NodePtr res_node = tree_it.GetNode();
  iterator res_it(res_node, nullptr);
  res_val.first = res_it;
  return res_val;
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  auto it = RBTree<key_type, mapped_type>::Find(key);
  if (it != this->end()) {
    RBTree<key_type, mapped_type>::Erase(it);
    auto res = insert(key, obj);
    res.second = false;
    return res;
  }
  return insert(key, obj);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  return RBTree<key_type, mapped_type>::Erase(pos);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map<key_type, mapped_type>& pos) {
  RBTree<key_type, mapped_type>::Swap(pos);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map<key_type, mapped_type>& pos) {
  RBTree<key_type, mapped_type>::Merge(pos);
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type& key) {
  return RBTree<key_type, mapped_type>::Contains(key);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::value_type&
map<key_type, mapped_type>::MapIterator::operator*() {
  std::pair<const key_type, mapped_type> temp_res =
      RBTree<key_type, mapped_type>::RBTreeIterator::current->data;
  std::pair<const key_type, mapped_type>& res = temp_res;
  return res;
}

template <typename key_type, typename mapped_type>
template <class... Args>
std::vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
map<key_type, mapped_type>::insert_many(Args&&... args) {
  std::vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
      res;
  for (const auto& a : {args...}) {
    res.push_back(insert(a));
  }
  return res;
}

}  // namespace s21