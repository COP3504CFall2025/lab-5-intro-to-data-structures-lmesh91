#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept override;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;


	void printForward() const;
	void printReverse() const;
};

// Functions that *do* things
template <typename T>
[[nodiscard]] size_t ABQ<T>::getSize() const noexcept {
    return curr_size_;
}

template <typename T>
[[nodiscard]] size_t ABQ<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template <typename T>
[[nodiscard]] T* ABQ<T>::getData() const noexcept {
    return array_;
}

template <typename T>
void ABQ<T>::enqueue(const T& data) {
    if (curr_size_ == capacity_) {
        T* new_array = new T[capacity_ * scale_factor_];
        for (size_t i = 0; i < curr_size_; i++) {
            new_array[i] = array_[i];
        }
        delete[] array_;
        array_ = new_array;
        capacity_ *= scale_factor_;
    }
    array_[curr_size_] = data;
    curr_size_++;
}

template <typename T>
T ABQ<T>::peek() const {
    if (curr_size_ == 0) {
        throw std::runtime_error("Cannot peek at empty queue");
    }
    return array_[0];
}

template <typename T>
T ABQ<T>::dequeue() {
    if (curr_size_ == 0) {
        throw std::runtime_error("Cannot pop empty queue");
    }
    T res = peek();
    for (size_t i = 0; i < curr_size_-1; i++) {
        array_[i] = array_[i+1];
    }
    curr_size_--;
    return res;
}

template <typename T>
void ABQ<T>::printForward() const {
    for (size_t i = 0; i < curr_size_; i++) {
        std::cout << array_[i] << std::endl;
    }
}

template <typename T>
void ABQ<T>::printReverse() const {
    for (size_t i = curr_size_ - 1; i >= 0; i--) {
        std::cout << array_[i] << std::endl;
    }
}

// Big 5 + Parameterized Constructor - Copied from ABS
template <typename T>
ABQ<T>::ABQ() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[1];
};

template <typename T>
ABQ<T>::ABQ(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity];
};

template <typename T>
ABQ<T>::ABQ(const ABQ& other) {
    T* array = new T[other.capacity_];
    for (size_t i = 0; i < other.curr_size_; i++) {
        array[i] = other.array_[i];
    }
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = array;
};

template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs) {
    if (&rhs == this) return *this;
    T* array = new T[rhs.capacity_];
    for (size_t i = 0; i < rhs.curr_size_; i++) {
        array[i] = rhs.array_[i];
    }
    delete[] array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = array;
    return *this;
};

template <typename T>
ABQ<T>::ABQ(ABQ&& other) noexcept {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;
    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
};

template <typename T>
ABQ<T>& ABQ<T>::operator=(ABQ<T>&& rhs) noexcept {
    if (&rhs == this) return *this;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = rhs.array_;
    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    rhs.array_ = nullptr;
    return *this;
};

template <typename T>
ABQ<T>::~ABQ() noexcept {
    delete[] array_;
    array_ = nullptr;
    capacity_ = 0;
    curr_size_ = 0;
};