namespace s21 {

// Vector Member functions
//________________________________________________________________________________
template <typename value_type>
vector<value_type>::vector() : arr(nullptr), m_size(0), m_capacity(0) {}

template <typename value_type>
vector<value_type>::vector(size_type size_vec) {
  if (size_vec > this->max_size()) {
    throw std::out_of_range("can't create vector larger then max_size()");
  }
  arr = new value_type[size_vec];
  m_size = size_vec;
  m_capacity = size_vec;
  for (size_type i = 0; i < m_size; i++) {
    arr[i] = 0;
  }
}
template <typename value_type>
vector<value_type>::vector(const vector<value_type> &other) {
  copy_vector(other);
}

template <typename value_type>
vector<value_type>::vector(vector<value_type> &&other) noexcept
    : arr(nullptr), m_size(0), m_capacity(0) {
  std::swap(this->arr, other.arr);
  std::swap(this->m_size, other.m_size);
  std::swap(this->m_capacity, other.m_capacity);
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> other) {
  init_list_copy(other);
}

template <typename value_type>
vector<value_type>::~vector() {
  free_vector();
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(
    vector<value_type> &&other) noexcept {
  if (this != &other) {
    free_vector();
    std::swap(this->arr, other.arr);
    std::swap(this->m_size, other.m_size);
    std::swap(this->m_capacity, other.m_capacity);
  }
  return *this;
}

//________________________________________________________________________________

// Vector Element access
//________________________________________________________________________________

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(
    size_type place) const {
  if (place >= m_size) {
    throw std::out_of_range("Out of range exception");
  }
  return arr[place];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type i) const {
  if (i >= m_size) {
    throw std::out_of_range("Out of range exception");
  }
  return arr[i];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  if (m_size == 0) {
    throw std::out_of_range("vector size is zero");
  }
  return arr[0];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  if (m_size == 0) {
    throw std::out_of_range("vector size is zero");
  }
  return arr[m_size - 1];
}

template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::data() {
  return arr;
}

//________________________________________________________________________________

// Vector Iterators
//________________________________________________________________________________

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(arr);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator((arr + m_size));
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin() const {
  return const_iterator(arr);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend() const {
  return const_iterator((arr + m_size));
}

//________________________________________________________________________________

// Vector Capacity
//________________________________________________________________________________

template <typename value_type>
bool vector<value_type>::empty() const {
  return m_size > 0 ? false : true;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return m_size;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() const {
  int bits = 0;
  size_type res = 0;
#if defined(__LP64__) || defined(_M_IA64)
  bits = 63;
#else
  bits = 31;
#endif
  if (bits == 63) {
    res = static_cast<size_type>(pow(2, 63)) / sizeof(int) - 1;
  } else {
    res = static_cast<size_type>(pow(2, 31)) / sizeof(int) - 1;
  }
  return res;
}

template <typename value_type>
void vector<value_type>::reserve(size_type count) {
  long int temp = count;
  if (temp < 0) {
    throw std::length_error("This memory out of range");
  }
  if (count > m_capacity) {
    pointer arr1 = new value_type[count];
    m_capacity = count;
    for (size_type i = 0; i < m_size; i++) {
      arr1[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = arr1;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return m_capacity;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  pointer new_arr = new value_type[m_size];
  std::copy(arr, arr + m_size, new_arr);
  delete[] arr;
  arr = new_arr;
  m_capacity = m_size;
}

//________________________________________________________________________________

// Vector Modifiers
//________________________________________________________________________________

template <typename value_type>
void vector<value_type>::clear() {
  delete[] arr;
  arr = new value_type[m_capacity];
  m_size = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const const_reference value) {
  size_type position = pos - begin();
  if (position > m_size) {
    throw std::out_of_range("Position is out of range");
  }
  if (m_size == m_capacity) {
    change_capacity();
  }
  iterator new_it = begin() + position;
  for (auto i = end(); i != new_it; --i) {
    *i = *(i - 1);
  }
  *new_it = value;
  m_size += 1;
  return new_it;
}

template <typename value_type>
void vector<value_type>::erase(vector<value_type>::iterator pos) {
  size_type position = pos - begin();
  if (position > m_size) {
    throw std::out_of_range("Position is out of range");
  }
  value_type tmp = arr[m_size - 1];
  for (auto i = m_size - 1; i > position; i--) {
    value_type prev = arr[i - 1];
    arr[i - 1] = tmp;
    tmp = prev;
  }
  m_size -= 1;
}

template <typename value_type>
void vector<value_type>::push_back(value_type new_value) {
  if (m_size >= m_capacity) {
    change_capacity();
  }
  arr[m_size++] = new_value;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (m_size > 0) {
    m_size--;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector<value_type> &other) {
  std::swap(this->arr, other.arr);
  std::swap(this->m_size, other.m_size);
  std::swap(this->m_capacity, other.m_capacity);
}

//________________________________________________________________________________

// Доп часть
//________________________________________________________________________________

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  vector<value_type> vec = {args...};
  vector<value_type>::iterator new_pos = begin() + (pos - cbegin());
  for (size_type i = 0; i < vec.size(); i++) {
    new_pos = insert(new_pos, vec[i]);
    ++new_pos;
  }
  return new_pos;
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}

//________________________________________________________________________________

// Вспомогательные методы
//________________________________________________________________________________

template <typename value_type>
void vector<value_type>::change_capacity() {
  if (m_capacity == 0) {
    arr = new value_type[1];
    m_capacity = 1;
  } else {
    pointer arr1 = new value_type[m_size * 2];
    m_capacity = m_size * 2;
    std::copy(arr, arr + m_size, arr1);
    delete[] arr;
    arr = arr1;
  }
}

template <typename value_type>
void vector<value_type>::free_vector() {
  delete[] arr;
  m_size = 0;
  m_capacity = 0;
  arr = nullptr;
}

template <typename value_type>
void vector<value_type>::copy_vector(const vector<value_type> &other) {
  this->m_size = other.size();
  this->arr = new value_type[this->m_size];
  for (size_type i = 0; i < m_size; i++) {
    this->arr[i] = other.at(i);
  }
  this->m_capacity = m_size;
}

template <typename value_type>
void vector<value_type>::init_list_copy(
    std::initializer_list<value_type> other) {
  arr = new value_type[other.size()];
  m_size = other.size();
  m_capacity = m_size;
  std::copy(other.begin(), other.end(), arr);
}

//________________________________________________________________________________

}  // namespace s21
