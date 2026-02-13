#pragma once

#include <cstddef>
#include <ostream>

// Fixed-size circular buffer that overwrites the oldest element when full.
// Uncopyable by design; moving is allowed.
template <typename T, std::size_t N>
class CircularBuffer
{
  static_assert(N >= 4, "Buffer size N must be at least 4");

public:
  CircularBuffer() = default;
  CircularBuffer(const CircularBuffer &) = delete;
  CircularBuffer &operator=(const CircularBuffer &) = delete;
  CircularBuffer(CircularBuffer &&) = default;
  CircularBuffer &operator=(CircularBuffer &&) = default;

  // Remove all stored elements.
  void clear() noexcept
  {
    head_ = 0;
    tail_ = 0;
    size_ = 0;
  }

  // Write an element; overwrites the oldest when the buffer is full.
  void write(const T &value)
  {
    data_[tail_] = value;
    if (size_ == N)
    {
      head_ = advance(head_);
    }
    else
    {
      ++size_;
    }
    tail_ = advance(tail_);
  }

  // Read (and remove) the oldest element. Returns false when the buffer is empty.
  bool read(T &out)
  {
    if (size_ == 0)
    {
      return false;
    }
    out = data_[head_];
    head_ = advance(head_);
    --size_;
    return true;
  }

  // Number of stored elements.
  std::size_t size() const noexcept { return size_; }

  // Whether the buffer is full.
  bool full() const noexcept { return size_ == N; }

  // Stream all stored elements from oldest to newest.
  template <typename U, std::size_t M>
  friend std::ostream &operator<<(std::ostream &os, const CircularBuffer<U, M> &buffer);

private:
  std::size_t advance(std::size_t index) const noexcept { return (index + 1) % N; }

  T data_[N]{};
  std::size_t head_{0}; // index of oldest element
  std::size_t tail_{0}; // index to write next element
  std::size_t size_{0};
};

template <typename U, std::size_t M>
std::ostream &operator<<(std::ostream &os, const CircularBuffer<U, M> &buffer)
{
  for (std::size_t i = 0, idx = buffer.head_; i < buffer.size_; ++i, idx = buffer.advance(idx))
  {
    os << buffer.data_[idx];
    if (i + 1 < buffer.size_)
    {
      os << ' ';
    }
  }
  return os;
}
