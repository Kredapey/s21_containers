
namespace s21 {
template <class value_type, class Container>
template <class... Args>
void queue<value_type, Container>::insert_many_back(Args &&...args) {
  for (auto v : std::initializer_list<value_type>{args...}) {
    push(v);
  }
}

template <class value_type, class Container>
s21::queue<value_type, Container> &queue<value_type, Container>::operator=(
    queue &&other) noexcept {
  data_ = std::move(other.data_);
  return *this;
}

template <class value_type, class Container>
s21::queue<value_type, Container> &queue<value_type, Container>::operator=(
    queue &other) {
  if (this != other) {
    data_ = data_.other;
  }
  return *this;
}

template <class value_type, class Container>
typename queue<value_type, Container>::reference
queue<value_type, Container>::back() {
  return data_.back();
}

template <class value_type, class Container>
typename queue<value_type, Container>::reference
queue<value_type, Container>::front() {
  if (empty()) throw std::out_of_range("queue is empty");
  return data_.front();
}

template <class value_type, class Container>
void queue<value_type, Container>::pop() {
  if (!empty()) data_.pop_front();
}

template <class value_type, class Container>
void queue<value_type, Container>::swap(queue &other) {
  if (this != &other) data_.swap(other.data_);
}

template <class value_type, class Container>
bool queue<value_type, Container>::empty() const {
  return !size();
}

template <class value_type, class Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::back() const {
  if (empty()) throw std::out_of_range("queue is empty");

  return data_.front();
}

template <class value_type, class Container>
typename queue<value_type, Container>::size_type
queue<value_type, Container>::size() const {
  return data_.size();
}

template <class value_type, class Container>
queue<value_type, Container>::queue() : data_() {}

template <class value_type, class Container>
queue<value_type, Container>::queue(
    std::initializer_list<value_type> const &items)
    : data_(items) {}

template <class value_type, class Container>
queue<value_type, Container>::queue(queue const &other) : data_(other.data_) {}

template <class value_type, class Container>
queue<value_type, Container>::queue(queue &&other) noexcept
    : data_(std::move(other.data_)) {}

template <class value_type, class Container>
queue<value_type, Container>::queue::~queue() {}

template <class value_type, class Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::front() const {
  return data_.front();
}

template <class value_type, class Container>
void queue<value_type, Container>::push(const value_type &value) {
  data_.push_back(value);
}

template <class value_type, class Container>
void queue<value_type, Container>::push(value_type &&value) {
  data_.push_back(value);
}

template <class value_type, class Container>
void queue<value_type, Container>::clear() {
  data_.clear();
}

template <class value_type, class Container>
typename queue<value_type, Container>::reference
queue<value_type, Container>::operator[](const size_type &i) {
  if (i >= size() || i < 0) throw std::out_of_range("out_of_range");
  return data_[i];
}

template <class value_type, class Container>
typename queue<value_type, Container>::const_reference
queue<value_type, Container>::operator[](const size_type &i) const {
  if (i >= size()) throw std::out_of_range("out_of_range");
  return data_[i];
}

}  // namespace s21
