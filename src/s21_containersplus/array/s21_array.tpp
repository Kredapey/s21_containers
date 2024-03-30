namespace s21 {
template <typename value_type, std::size_t N>
array<value_type, N>::array() : m_size(N) {}

template <typename value_type, std::size_t N>
array<value_type, N>::array(std::initializer_list<value_type> const &items)
    : m_size(N) {
  if (items.size() > m_size) {
    throw std::out_of_range("too many initializers");
  }
  std::copy(items.begin(), items.end(), arr);
}

template <typename value_type, std::size_t N>
array<value_type, N>::array(const array<value_type, N> &a) : m_size(N) {
  for (size_type i = 0; i < a.m_size; i++) {
    arr[i] = a.arr[i];
  }
}

template <typename value_type, std::size_t N>
array<value_type, N>::array(array<value_type, N> &&a) : m_size(0) {
  std::swap(arr, a.arr);
  std::swap(m_size, a.m_size);
}

template <typename value_type, std::size_t N>
array<value_type, N> &array<value_type, N>::operator=(
    array<value_type, N> &&a) {
  if (this != &a) {
    for (size_type i = 0; i < a.m_size; i++) {
      arr[i] = std::move(a.arr[i]);
    }
  }
  return *this;
}

template <typename value_type, std::size_t N>
array<value_type, N> &array<value_type, N>::operator=(
    const array<value_type, N> &a) {
  for (size_type i = 0; i < a.m_size; i++) {
    arr[i] = a.arr[i];
  }
  m_size = a.m_size;
  return *this;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::at(
    size_type index) {
  if (index >= m_size) {
    throw std::out_of_range("index is out of range");
  }
  return arr[index];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::at(
    size_type index) const {
  if (index >= m_size) {
    throw std::out_of_range("index is out of range");
  }
  return arr[index];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::operator[](
    size_type index) {
  if (index >= m_size) {
    throw std::out_of_range("index is out of range");
  }
  return arr[index];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::operator[](
    size_type index) const {
  if (index >= m_size) {
    throw std::out_of_range("index is out of range");
  }
  return arr[index];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::front()
    const {
  if (m_size == 0) {
    throw std::out_of_range("array size is 0");
  }
  return arr[0];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::back()
    const {
  if (m_size == 0) {
    throw std::out_of_range("array size is 0");
  }
  return arr[m_size - 1];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::pointer array<value_type, N>::data() {
  return arr;
}

template <typename value_type, std::size_t N>
bool array<value_type, N>::empty() const {
  return m_size > 0 ? false : true;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::size_type array<value_type, N>::size() const {
  return m_size;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::size_type array<value_type, N>::max_size()
    const {
  return m_size;
}

template <typename value_type, std::size_t N>
void array<value_type, N>::swap(array<value_type, N> &other) {
  std::swap(this->arr, other.arr);
  std::swap(this->m_size, other.m_size);
}

template <typename value_type, std::size_t N>
void array<value_type, N>::fill(const_reference value) {
  for (size_type i = 0; i < m_size; i++) {
    arr[i] = value;
  }
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::iterator array<value_type, N>::begin() {
  return iterator(arr);
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::iterator array<value_type, N>::end() {
  return iterator(arr + m_size);
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::const_iterator array<value_type, N>::cbegin()
    const {
  return const_iterator(arr);
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::const_iterator array<value_type, N>::cend()
    const {
  return const_iterator(arr + m_size);
}

}  // namespace s21
