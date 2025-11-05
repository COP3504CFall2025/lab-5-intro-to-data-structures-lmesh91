#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

	void printForward() const;
	void printReverse() const;

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

// Functions that *do* things
template <typename T>
[[nodiscard]] size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}

template <typename T>
[[nodiscard]] size_t ABS<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template <typename T>
[[nodiscard]] T* ABS<T>::getData() const noexcept {
    return array_;
}

template <typename T>
void ABS<T>::push(const T& data) {
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
T ABS<T>::peek() const {
    if (curr_size_ == 0) {
        throw std::runtime_error("Cannot peek at empty stack");
    }
    return array_[curr_size_ - 1];
}

template <typename T>
T ABS<T>::pop() {
    if (curr_size_ == 0) {
        throw std::runtime_error("Cannot pop empty stack");
    }
    curr_size_--;
    return array_[curr_size_];
}

template <typename T>
void ABS<T>::printForward() const {
    for (size_t i = 0; i < curr_size_; i++) {
        std::cout << array_[i] << std::endl;
    }
}

template <typename T>
void ABS<T>::printReverse() const {
    for (size_t i = curr_size_ - 1; i >= 0; i--) {
        std::cout << array_[i] << std::endl;
    }
}

// Big 5 + Parameterized Constructor
template <typename T>
ABS<T>::ABS() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[1];
};

template <typename T>
ABS<T>::ABS(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity];
};

template <typename T>
ABS<T>::ABS(const ABS& other) {
    T* array = new T[other.capacity_];
    for (size_t i = 0; i < other.curr_size_; i++) {
        array[i] = other.array_[i];
    }
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = array;
};

template <typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs) {
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
ABS<T>::ABS(ABS&& other) noexcept {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = other.array_;
    other.capacity_ = 0;
    other.curr_size_ = 0;
    other.array_ = nullptr;
};

template <typename T>
ABS<T>& ABS<T>::operator=(ABS<T>&& rhs) noexcept {
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
ABS<T>::~ABS() noexcept {
    delete[] array_;
    array_ = nullptr;
    capacity_ = 0;
    curr_size_ = 0;
};