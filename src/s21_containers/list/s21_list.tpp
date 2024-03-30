namespace s21 {
template <class value_type>
list<value_type>::list() {
  basic_constructor();
  bind();
}

template <class value_type>
list<value_type>::list(const list &other) : list() {
  copy(other);
}

template <class value_type>
list<value_type>::list(list &&other) noexcept {
  basic_constructor();
  swap(other);
}

template <class value_type>
list<value_type>::list(std::initializer_list<value_type> init) : list() {
  for (auto &it : init) {
    push_back(it);
  }
}

template <class value_type>
list<value_type>::list(size_type n) : list() {
  if (n > max_size()) throw std::out_of_range("value is so big");
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <class value_type>
list<value_type>::~list() {
  clear();

  delete top_;

  delete bottom_;
}

template <class value_type>
void list<value_type>::copy(const list &other) {
  if (other.size_ > 0) {
    for (iterator iter = other.begin(); iter != other.end(); iter++) {
      push_back(iter.iter_node->value_);
    }
  }
}

template <class value_type>
void list<value_type>::basic_constructor() {
  size_ = 0;
  bottom_ = new Node(value_type());
  top_ = new Node(*bottom_);
}

template <class value_type>
void list<value_type>::bind() {
  top_->next_ = bottom_;
  bottom_->prev_ = top_;
}

template <class value_type>
typename list<value_type>::list &list<value_type>::operator=(
    list &&other) noexcept {
  if (this != &other) {
    clear();
    swap(other);
  }
  return *this;
}

template <class value_type>
typename list<value_type>::list &list<value_type>::operator=(
    const list &other) {
  if (this != &other) {
    size_ = other.size_;
    top_ = other.top_;
    bottom_ = other.bottom_;
  }
  return *this;
}

template <class value_type>
void list<value_type>::add_func_for_front_push(Node *node) {
  if (empty()) {
    add_func_for_empty_push(node);
    delete node;
  } else {
    node->next_ = top_;
    top_->prev_ = node;
    top_ = node;
  }
  changeSize(true);
}

template <class value_type>
void list<value_type>::add_func_for_push_back(Node *node) {
  if (empty()) {
    add_func_for_empty_push(node);
    delete node;
  } else {
    Node *temp = bottom_->prev_;
    temp->next_ = node;
    node->prev_ = temp;
    node->next_ = bottom_;
    bottom_->prev_ = node;
  }
  changeSize(true);
}

template <class value_type>
void list<value_type>::changeSize(bool flag) {
  if (flag) {
    ++size_;
  } else {
    --size_;
  }
}

template <class value_type>
void list<value_type>::add_func_for_empty_push(Node *node) {
  top_->value_ = node->value_;
}

template <class value_type>
int list<value_type>::distance(iterator top, iterator bottom) {
  auto index_top = 0, index_end = 0;
  for (iterator i = begin(); i != end(); ++i) {
    index_top++;
    if (top == i) {
      break;
    }
  }

  for (iterator i = begin(); i != end(); ++i) {
    index_end++;
    if (bottom == i) {
      break;
    }
  }

  int size = 0;

  if (index_top == index_end) {
  } else if (index_top < index_end) {
    for (iterator i = top; i != bottom; ++i) {
      ++size;
    }
  } else {
    for (iterator i = bottom; i != top; ++i) {
      ++size;
    }
    size = -size;
  }
  return size;
}

template <class value_type>
typename list<value_type>::size_type list<value_type>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <class value_type>
typename list<value_type>::size_type list<value_type>::size() const {
  return size_;
}

template <class value_type>
bool list<value_type>::empty() const {
  return size_ == 0;
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(top_);
}

template <class value_type>
typename list<value_type>::const_iterator list<value_type>::begin() const {
  return const_iterator(top_);
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(bottom_);
}

template <class value_type>
typename list<value_type>::const_iterator list<value_type>::end() const {
  return const_iterator(bottom_);
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  return (bottom_->prev_) ? bottom_->prev_->value_ : bottom_->value_;
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  return (empty) ? bottom_->value_ : top_->value_;
}

template <class value_type>
typename list<value_type>::reference list<value_type>::front() {
  return reference(top_->value_);
}

template <class value_type>
typename list<value_type>::reference list<value_type>::back() {
  return reference(bottom_->prev_->value_);
}

template <class value_type>
void list<value_type>::clear() {
  while (size_ > 0) {
    pop_front();
  }
}

template <class value_type>
void list<value_type>::swap(list &&other) noexcept {
  std::swap(top_, other.top_);
  std::swap(bottom_, other.bottom_);
  std::swap(size_, other.size_);
}

template <class value_type>
void list<value_type>::swap(list &other) {
  std::swap(top_, other.top_);
  std::swap(bottom_, other.bottom_);
  std::swap(size_, other.size_);
}

template <class value_type>
int list<value_type>::getIndex(iterator item) const {
  int i = 0;
  for (iterator it = begin(); it != end(); ++it) {
    if (item == it) {
      return i;
    } else {
      i++;
    }
  }
  return -1;
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::getByIndex(
    int index) const {
  int i = 0;
  for (iterator it = begin(); it != end(); ++it) {
    if (index == i) {
      return it;
    } else {
      i++;
    }
  }
  return nullptr;
}

template <class value_type>
void list<value_type>::sort() {
  if (size_ <= 1) {
    return;
  } else {
    iterator last = --end();
    quickSort(0, getIndex(last));
  }
}

template <class value_type>
int list<value_type>::partite(int left, int right) {
  iterator rigth_by_index = getByIndex(right);

  int pivot = rigth_by_index.iter_node->value_;
  int i = left;

  for (int j = left; j < right; j++) {
    if (getByIndex(j).iter_node->value_ < pivot) {
      iterator item_i = getByIndex(i);
      iterator item_j = getByIndex(j);
      int temp = item_i.iter_node->value_;
      item_i.iter_node->value_ = item_j.iter_node->value_;
      item_j.iter_node->value_ = temp;
      i++;
    }
  }
  iterator item_i = getByIndex(i);
  int temp = item_i.iter_node->value_;
  item_i.iter_node->value_ = rigth_by_index.iter_node->value_;
  rigth_by_index.iter_node->value_ = temp;

  return i;
}

template <class value_type>
void list<value_type>::quickSort(int left, int right) {
  if (left < right) {
    int p = partite(left, right);
    quickSort(left, p - 1);
    quickSort(p + 1, right);
  }
}

template <class value_type>
void list<value_type>::unique() {
  if (size_ > 1) {
    iterator temp = begin(), iter = ++begin();
    for (iter = ++begin(); iter != end(); iter++) {
      if (*iter == *temp) {
        erase(temp);
        temp = iter = begin();
      } else {
        ++temp;
      }
    }
  }
}

template <class value_type>
void list<value_type>::reverse() {
  if (size_ <= 1) {
    return;
  } else {
    size_type size = 0;
    for (iterator iter = begin(); size < size_;) {
      iterator i = iter;
      ++i;
      std::swap(iter.iter_node->next_, iter.iter_node->prev_);
      iter = i;
      ++size;
    }
    std::swap(top_, bottom_->prev_);
    bottom_->prev_->next_ = top_->prev_;
    top_->prev_ = nullptr;
  }
}

template <class value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (empty()) {
    copy(other);
  } else if (other.empty()) {
  } else {
    for (iterator iter = begin(); iter != end(); ++iter) {
      if (pos == iter) {
        for (iterator it = other.begin(); it != other.end(); ++it)
          insert(iter, it.iter_node->value_);
        break;
      }
    }
    other.clear();
  }
}

template <class value_type>
void list<value_type>::merge(list &other) {
  if (empty() && !other.empty()) {
    copy(other);
    other.clear();
  } else if (!empty() && !other.empty()) {
    iterator this_iter = begin(), other_iter = other.begin();
    while (this_iter != end()) {
      if (other_iter == other.end()) break;
      if (this_iter.iter_node->value_ >= other_iter.iter_node->value_) {
        insert(this_iter, other_iter.iter_node->value_);
        ++other_iter;
      } else {
        ++this_iter;
      }
    }
    if (other_iter != other.end()) {
      for (iterator it = other_iter; it != other.end(); ++it) {
        insert(this_iter, it.iter_node->value_);
      }
    }
    other.clear();
  }
}

template <class value_type>
typename list<value_type>::reference list<value_type>::operator[](
    const size_type i) {
  if (i >= size_) {
    throw std::out_of_range("index < 0 or index > size()");
  }
  iterator iter = begin();
  for (size_type it = 0; it < size_; ++it) {
    if (it == i) {
      break;
    }
    ++iter;
  }
  return iter.iter_node->value_;
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::operator[](
    const size_type i) const {
  if (i < 0 || i >= size_) {
    throw std::out_of_range("index < 0 or index > size()");
  }
  iterator iter = begin();
  for (size_type it = 0; it < size_; ++it) {
    if (it == i) {
      break;
    }
    ++iter;
  }
  return iter.iter_node->value_;
}

template <class value_type>
void list<value_type>::pop_front() {
  if (empty()) throw std::out_of_range("empty list");
  if (size_ == 1) {
    top_->value_ = value_type();
  } else {
    Node *node = top_;
    top_ = top_->next_;
    top_->prev_ = node->next_ = nullptr;
    delete node;
  }
  changeSize(false);
}

template <class value_type>
void list<value_type>::push_front(value_type &&value) {
  Node *node = new Node(value);
  add_func_for_front_push(node);
}

template <class value_type>
void list<value_type>::pop_back() {
  if (empty()) throw std::out_of_range("empty list");

  if (size_ == 1) {
    top_->value_ = value_type();
  } else {
    Node *last = bottom_->prev_;
    Node *last_prev = last->prev_;
    last_prev->next_ = bottom_;
    bottom_->prev_ = last_prev;
    last->next_ = last->prev_ = nullptr;
    delete last;
  }
  changeSize(false);
}

template <class value_type>
void list<value_type>::push_back(const_reference value) {
  Node *node = new Node(value);
  add_func_for_push_back(node);
}

template <class value_type>
void list<value_type>::push_back(value_type &&value) {
  Node *node = new Node(value);
  add_func_for_push_back(node);
}

template <class value_type>
void list<value_type>::push_front(const_reference &value) {
  Node *node = new Node(value);
  add_func_for_front_push(node);
}

template <class value_type>
void list<value_type>::erase(iterator pos) {
  if (empty()) {
    throw std::out_of_range("list is empty");
  } else if (pos == begin()) {
    pop_front();
  } else if (pos == end()) {
    throw std::out_of_range("element is null");
  } else {
    Node *node = top_;
    for (iterator iter = begin(); iter != end(); iter++) {
      if (iter == pos) {
        Node *temp = node;
        node->prev_->next_ = temp->next_;
        node->next_->prev_ = temp->prev_;
        delete node;
        changeSize(false);
        break;
      }
      node = node->next_;
    }
  }
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::insert(
    const_iterator pos, const_reference value) {
  iterator ret;
  if (pos == begin() || empty()) {
    push_front(value);
    ret = begin();
  } else if (pos == end()) {
    push_back(value);
    ret = end();
  } else {
    Node *node = new Node(value);
    for (ret = begin(); ret != end(); ++ret) {
      if (ret == pos) {
        node->prev_ = ret.iter_node->prev_;
        node->next_ = ret.iter_node;
        ret.iter_node->prev_->next_ = node;
        ret.iter_node->prev_ = node;
        changeSize(true);
        break;
      }
    }
  }

  return ret;
}

template <class value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  iterator iter = begin();
  if (pos == begin()) {
    insert_many_front(args...);
  } else {
    for (iterator it = begin(); it != end(); ++it) {
      if (it == pos) {
        iter = it;
        add_insert_many(pos, args...);
        break;
      }
    }
  }
  return iter;
}

template <class value_type>
template <typename... Args>
void list<value_type>::add_insert_many(const_iterator pos, Args &&...args) {
  for (auto v : std::initializer_list<value_type>{args...}) {
    insert(pos, v);
  }
}

template <class value_type>
template <typename... Args>
void list<value_type>::insert_many_front(Args &&...args) {
  for (auto v : std::initializer_list<value_type>{args...}) {
    push_front(v);
  }
}

template <class value_type>
template <typename... Args>
void list<value_type>::insert_many_back(Args &&...args) {
  for (auto v : std::initializer_list<value_type>{args...}) {
    push_back(v);
  }
}

}  // namespace s21
