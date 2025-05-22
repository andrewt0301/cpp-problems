//
// Created by Andrei Tatarnikov on 2019-05-19.
//

#ifndef TUTORIALS_HEAP_H
#define TUTORIALS_HEAP_H

inline size_t parent(size_t i) {
  return (i - 1) / 2;
}

inline size_t left(size_t i) {
  return 2 * i + 1;
}

inline size_t right(size_t i) {
  return 2 * i + 2;
}

template <typename T>
inline void swap(T& a, size_t i, size_t j) {
  auto tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

template <typename T, typename TPred>
void heapify(T& a, size_t size, size_t i, TPred pred) {
  size_t top = i;
  const size_t l = left(i);
  if (l < size && pred(a[l], a[top])) {
    top = l;
  }
  const size_t r = right(i);
  if (r < size && pred(a[r], a[top])) {
    top = r;
  }
  if (top != i) {
    swap(a, i, top);
    heapify(a, size, top, pred);
  }
}

template <typename T, typename TPred>
void buildHeap(T& a, size_t size, TPred pred) {
  size_t i = size / 2 + 1;
  while(i != 0) {
    heapify(a, size, --i, pred);
  }
}

template <typename T, typename TPred>
void heapsort(T& a, size_t size, TPred pred) {
  buildHeap(a, size, pred);
  for (size_t i = size - 1; i >= 1; i--) {
    swap(a, i, 0);
    size--;
    heapify(a, size, 0, pred);
  }
}

#endif //TUTORIALS_HEAP_H
