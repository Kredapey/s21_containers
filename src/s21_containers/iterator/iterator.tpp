#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_ITERATOR_S21_ITERATOR_TPP
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_ITERATOR_S21_ITERATOR_TPP

namespace s21 {
// Итератор
//________________________________________________________________________________

template <typename value_type>
VecArrIterator<value_type>::VecArrIterator(pointer value) : val(value) {}

template <typename value_type>
VecArrIterator<value_type>::VecArrIterator(const VecArrIterator &iter) : val(iter.val) {}

template <typename value_type>
VecArrIterator<value_type>& VecArrIterator<value_type>::operator=(const VecArrIterator<value_type>& iter) {
  this->val = iter.val;
  return *this;
}

template <typename value_type>
VecArrIterator<value_type>& VecArrIterator<value_type>::operator=(VecArrIterator<value_type>&& iter) {
  this->val = nullptr;
  std::swap(this->val, iter.val);
  return *this;
}

template <typename value_type>
bool VecArrIterator<value_type>::operator!=(const VecArrIterator &other) const {
  return val != other.val;
}

template <typename value_type>
bool VecArrIterator<value_type>::operator==(const VecArrIterator &other) const {
  return val == other.val;
}

template <typename value_type>
bool VecArrIterator<value_type>::operator>(const VecArrIterator &other) const {
  return val > other.val;
}

template <typename value_type>
bool VecArrIterator<value_type>::operator>=(const VecArrIterator &other) const {
  return val >= other.val;
}

template <typename value_type>
bool VecArrIterator<value_type>::operator<(const VecArrIterator &other) const {
  return val < other.val;
}

template <typename value_type>
bool VecArrIterator<value_type>::operator<=(const VecArrIterator &other) const {
  return val <= other.val;
}

template <typename value_type>
typename VecArrIterator<value_type>::reference VecArrIterator<value_type>::operator*()
    const {
  return *val;
}

template <typename value_type>
VecArrIterator<value_type> &VecArrIterator<value_type>::operator++() {
  ++val;
  return *this;
}

template <typename value_type>
VecArrIterator<value_type> &VecArrIterator<value_type>::operator--() {
  --val;
  return *this;
}

template <typename value_type>
VecArrIterator<value_type> &VecArrIterator<value_type>::operator++(int) {
  val++;
  return *this;
}

template <typename value_type>
VecArrIterator<value_type> &VecArrIterator<value_type>::operator--(int) {
  val++;
  return *this;
}

template <typename value_type>
VecArrIterator<value_type> VecArrIterator<value_type>::operator-(
    size_type value) const {
  VecArrIterator<value_type> iter(*this);
  for (size_type i = 0; i < value; i++) {
    --iter;
  }
  return iter;
}

template <typename value_type>
VecArrIterator<value_type> VecArrIterator<value_type>::operator+(
    size_type value) const {
  VecArrIterator<value_type> iter(*this);
  for (size_type i = 0; i < value; i++) {
    ++iter;
  }
  return iter;
}

template <typename value_type>
VecArrIterator<value_type> &VecArrIterator<value_type>::operator+=(size_type value) {
  for (size_type i = 0; i < value; i++) {
    ++val;
  }
  return *this;
}

template <typename value_type>
VecArrIterator<value_type> &VecArrIterator<value_type>::operator-=(size_type value) {
  for (size_type i = 0; i < value; i++) {
    --val;
  }
  return *this;
}

template <typename value_type>
typename VecArrIterator<value_type>::size_type VecArrIterator<value_type>::operator-(
    const VecArrIterator<value_type> &other) const {
  return val - other.val;
}

template <typename value_type>
typename VecArrIterator<value_type>::pointer VecArrIterator<value_type>::operator->() {
  return val;
}

//________________________________________________________________________________

// Константный Итератор
//________________________________________________________________________________

template <typename value_type>
VecArrConstIterator<value_type>::VecArrConstIterator(pointer value) : val(value) {}

template <typename value_type>
VecArrConstIterator<value_type>::VecArrConstIterator(const_pointer value) : val(value) {}

template <typename value_type>
VecArrConstIterator<value_type>::VecArrConstIterator(const VecArrConstIterator &iter)
    : val(iter.val) {}

template <typename value_type>
bool VecArrConstIterator<value_type>::operator!=(
    const VecArrConstIterator &other) const {
  return val != other.val;
}

template <typename value_type>
bool VecArrConstIterator<value_type>::operator==(
    const VecArrConstIterator &other) const {
  return val == other.val;
}

template <typename value_type>
bool VecArrConstIterator<value_type>::operator>(
    const VecArrConstIterator &other) const {
  return val > other.val;
}

template <typename value_type>
bool VecArrConstIterator<value_type>::operator>=(
    const VecArrConstIterator &other) const {
  return val >= other.val;
}

template <typename value_type>
bool VecArrConstIterator<value_type>::operator<(
    const VecArrConstIterator &other) const {
  return val < other.val;
}

template <typename value_type>
bool VecArrConstIterator<value_type>::operator<=(
    const VecArrConstIterator &other) const {
  return val <= other.val;
}

template <typename value_type>
typename VecArrConstIterator<value_type>::value_type
VecArrConstIterator<value_type>::operator*() const {
  return *val;
}

template <typename value_type>
VecArrConstIterator<value_type> &VecArrConstIterator<value_type>::operator++() {
  ++val;
  return *this;
}

template <typename value_type>
VecArrConstIterator<value_type> &VecArrConstIterator<value_type>::operator--() {
  --val;
  return *this;
}

template <typename value_type>
VecArrConstIterator<value_type> &VecArrConstIterator<value_type>::operator++(int) {
  val++;
  return *this;
}

template <typename value_type>
VecArrConstIterator<value_type> &VecArrConstIterator<value_type>::operator--(int) {
  val++;
  return *this;
}

template <typename value_type>
VecArrConstIterator<value_type> VecArrConstIterator<value_type>::operator-(
    size_type value) const {
  VecArrConstIterator<value_type> iter(*this);
  for (int i = 0; i < value; i++) {
    --iter;
  }
  return iter;
}

template <typename value_type>
VecArrConstIterator<value_type> VecArrConstIterator<value_type>::operator+(
    size_type value) const {
  VecArrConstIterator<value_type> iter(*this);
  for (size_type i = 0; i < value; i++) {
    ++iter;
  }
  return iter;
}

template <typename value_type>
VecArrConstIterator<value_type> &VecArrConstIterator<value_type>::operator+=(
    size_type value) {
  for (size_type i = 0; i < value; i++) {
    ++val;
  }
  return *this;
}

template <typename value_type>
VecArrConstIterator<value_type> &VecArrConstIterator<value_type>::operator-=(
    size_type value) {
  for (size_type i = 0; i < value; i++) {
    --val;
  }
  return *this;
}

template <typename value_type>
typename VecArrConstIterator<value_type>::size_type
VecArrConstIterator<value_type>::operator-(
    const VecArrConstIterator<value_type> &other) const {
  return val - other.val;
}

template <typename value_type>
typename VecArrConstIterator<value_type>::pointer
VecArrConstIterator<value_type>::operator->() {
  return val;
}
} // namespace s21

#endif // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINERS_ITERATOR_S21_ITERATOR_TPP