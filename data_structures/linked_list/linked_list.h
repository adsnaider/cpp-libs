namespace data_structures {
namespace linked_list {

template <typename T>
class linked_list {
 public:
  template <typename Value>
  class base_iterator;

 private:
  struct node;

 public:
  typedef T value_type;
  typedef unsigned int size_t;

  typedef base_iterator<value_type> iterator;
  typedef base_iterator<const value_type> const_iterator;

  friend iterator;
  friend const_iterator;

  linked_list();
  linked_list(const linked_list &other);

  value_type &front();
  value_type front() const;

  value_type &back();
  value_type back() const;

  size_t size() const;

  void insert(const_iterator it, const value_type &t);
  void pop(const_iterator it);

  bool empty() const;
  void clear();

  iterator begin();
  iterator end();

  iterator rbegin();
  iterator rend();

  const_iterator cbegin() const;
  const_iterator cend() const;

  const_iterator crbegin() const;
  const_iterator crend() const;

  ~linked_list();

 private:
  node *head_;
  node *tail_;
  size_t size_;

  void destroy_list(node *n1, node *n2);

  struct node {
    node() : next(nullptr), prev(nullptr) {}
    node(const value_type &data, node *next = nullptr, node *previous = nullptr)
        : next(next), prev(previous), data(data) {}
    node *next;
    node *prev;
    value_type data;
  };

 public:
  template <typename Value>
  class base_iterator {
    friend linked_list;

   public:
    base_iterator(node *n) : index(n) {}
    Value &operator*() { return index->data; }
    base_iterator &operator++() {
      index = index->next;
      return *this;
    }
    base_iterator &operator--() {
      index = index->prev;
      return *this;
    }

    template <typename U>
    friend bool operator==(const base_iterator<U> &it1,
                           const base_iterator<U> &it2) {
      return it1.index == it2.index;
    }
    template <typename U>
    friend bool operator!=(const base_iterator<U> &it1,
                           const base_iterator<U> &it2) {
      return !(it1.index == it2.index);
    }

   protected:
    node *index;
  };
};

template <typename T>
linked_list<T>::linked_list() : head_(nullptr), tail_(nullptr), size_(0) {
  head_ = new node();
  tail_ = new node();
  head_->next = tail_;
  tail_->prev = head_;
}

template <typename T>
linked_list<T>::linked_list(const linked_list<T> &other) : linked_list() {
  if (other.head_ == nullptr) return;
  for (auto it = other.cbegin(); it != other.cend(); ++it) {
    insert(cend(), *it);
  }
}

template <typename T>
typename linked_list<T>::value_type &linked_list<T>::front() {
  return head_->next->data;
}
template <typename T>
typename linked_list<T>::value_type linked_list<T>::front() const {
  return head_->next->data;
}

template <typename T>
typename linked_list<T>::value_type &linked_list<T>::back() {
  return tail_->prev->data;
}
template <typename T>
typename linked_list<T>::value_type linked_list<T>::back() const {
  return tail_->prev->data;
}

template <typename T>
typename linked_list<T>::size_t linked_list<T>::size() const {
  return size_;
}

template <typename T>
void linked_list<T>::insert(const_iterator it, const value_type &t) {
  node *post = it.index;
  node *prev = new node(t);
  prev->next = post;
  prev->prev = post->prev;
  prev->next->prev = prev;
  prev->prev->next = prev;
  ++size_;
}

template <typename T>
void linked_list<T>::pop(const_iterator it) {
  node *index = it.index;
  index->prev->next = index->next;
  index->next->prev = index->prev;
  delete index;
  --size_;
}

template <typename T>
bool linked_list<T>::empty() const {
  return size_ == 0;
}
template <typename T>
void linked_list<T>::clear() {
  destroy_list(head_->next, tail_);
  size_ = 0;
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::begin() {
  return iterator(head_->next);
}
template <typename T>
typename linked_list<T>::iterator linked_list<T>::end() {
  return iterator(tail_);
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::rbegin() {
  return iterator(tail_->prev);
}
template <typename T>
typename linked_list<T>::iterator linked_list<T>::rend() {
  return iterator(head_);
}

template <typename T>
typename linked_list<T>::const_iterator linked_list<T>::cbegin() const {
  return const_iterator(head_->next);
}
template <typename T>
typename linked_list<T>::const_iterator linked_list<T>::cend() const {
  return const_iterator(tail_);
}

template <typename T>
typename linked_list<T>::const_iterator linked_list<T>::crbegin() const {
  return const_iterator(tail_->prev);
}
template <typename T>
typename linked_list<T>::const_iterator linked_list<T>::crend() const {
  return const_iterator(head_);
}

template <typename T>
linked_list<T>::~linked_list() {
  clear();
  delete head_;
  delete tail_;
}

template <typename T>
void linked_list<T>::destroy_list(node *n1, node *n2) {
  if (n1 == nullptr or n1 == n2) return;
  destroy_list(n1->next, n2);
  delete n1;
}

}  // namespace linked_list
}  // namespace data_structures
