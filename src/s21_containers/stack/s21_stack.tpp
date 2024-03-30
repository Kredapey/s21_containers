namespace s21 {

template <class value_type, class Container>
template <typename... Args>
void stack<value_type, Container>::insert_many_front(Args &&...args) {
  data_.insert_many_back(args...);
}

template <class value_type, class Container>
typename stack<value_type, Container>::const_reference
stack<value_type, Container>::operator[](const size_type index) const {
  if (index >= size()) throw std::out_of_range("out of range");
  return data_[index];
}

template <class value_type, class Container>
typename stack<value_type, Container>::reference
stack<value_type, Container>::operator[](const size_type index) {
  if (index >= size()) throw std::out_of_range("out of range");
  return data_[index];
}

template <class value_type, class Container>
stack<value_type, Container> &stack<value_type, Container>::operator=(
    stack &&other) noexcept {
  if (this != &other) data_ = std::move(other.data_);
  return *this;
}

template <class value_type, class Container>
stack<value_type, Container> &stack<value_type, Container>::operator=(
    stack &other) {
  if (this != &other) data_ = data_.other;
  return *this;
}

template <class value_type, class Container>
typename stack<value_type, Container>::reference
stack<value_type, Container>::top() {
  if (empty()) {
    throw std::out_of_range("stack is empty");
  }
  return data_.back();
}

template <class value_type, class Container>
typename stack<value_type, Container>::const_reference
stack<value_type, Container>::top() const {
  if (empty()) {
    throw std::out_of_range("stack is empty");
  }
  return data_.back();
}

template <class value_type, class Container>
void stack<value_type, Container>::swap(stack &other) {
  if (this != &other) data_.swap(other.data_);
}

template <class value_type, class Container>
bool stack<value_type, Container>::empty() const {
  return !size();
}

template <class value_type, class Container>
typename stack<value_type, Container>::size_type
stack<value_type, Container>::size() const {
  return data_.size();
}

template <class value_type, class Container>
stack<value_type, Container>::stack() : data_() {}

template <class value_type, class Container>
stack<value_type, Container>::stack(
    std::initializer_list<value_type> const &items)
    : data_(items) {}

template <class value_type, class Container>
stack<value_type, Container>::stack(const stack &other) : data_(other.data_) {}

template <class value_type, class Container>
stack<value_type, Container>::stack(stack &&other) noexcept
    : data_(std::move(other.data_)) {}

template <class value_type, class Container>
stack<value_type, Container>::stack::~stack() {}

template <class value_type, class Container>
void stack<value_type, Container>::push(const value_type &value) {
  data_.push_back(value);
}

template <class value_type, class Container>
void stack<value_type, Container>::push(value_type &&value) {
  data_.push_back(value);
}

template <class value_type, class Container>
void stack<value_type, Container>::pop() {
  if (!empty()) data_.pop_back();
}

template <class value_type, class Container>
void stack<value_type, Container>::clear() {
  data_.clear();
}
}  // namespace s21
