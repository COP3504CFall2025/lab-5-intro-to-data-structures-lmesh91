#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    size_t capacity_;    // total allocated capacity
    size_t size_;        // number of stored elements
    size_t front_;       // index of front element
    size_t back_;        // index after the last element (circular)

    static constexpr size_t SCALE_FACTOR = 2;

    size_t p_inc(size_t& p) const; // Increment/decrement front/back pointers for circular buffer
    size_t p_dec(size_t& p) const; // These work like ++i or --i, returning the value after incrementing

public:
    // Big 5
    ABDQ();
    explicit ABDQ(size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() override;

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    void ensureCapacity();
    void shrinkIfNeeded();

    // Getters
    size_t getSize() const noexcept override;

	void PrintForward() const;
	void PrintReverse() const;
};

// Helper functions
template <typename T>
size_t ABDQ<T>::p_inc(size_t& p) const {
    p = (p+1) % capacity_;
    return p;
}

template <typename T>
size_t ABDQ<T>::p_dec(size_t& p) const {
    p = (p+capacity_-1) % capacity_;
    return p;
}

// Functions that *do* things
template <typename T>
[[nodiscard]] size_t ABDQ<T>::getSize() const noexcept {
    return size_;
}

template <typename T>
void ABDQ<T>::PrintForward() const {
    for (size_t i = 0; i < size_; i++) {
        std::cout << data_[(i+front_)%capacity_] << std::endl;
    }
}
template <typename T>
void ABDQ<T>::PrintReverse() const {
    for (size_t i = size_ - 1; i >= 0; i++) {
        std::cout << data_[(i+front_)%capacity_] << std::endl;
    }
}

template <typename T>
void ABDQ<T>::pushFront(const T& item) {
    ensureCapacity();
    data_[p_dec(front_)] = item;
    size_++;
}
template <typename T>
void ABDQ<T>::pushBack(const T& item) {
    ensureCapacity();
    data_[back_] = item;
    p_inc(back_);
    size_++;
}

template <typename T>
T ABDQ<T>::popFront() {
    if (size_ == 0) {
        throw std::runtime_error("Cannot pop empty dequeue");
    }
    T res = data_[front_];
    p_inc(front_);
    size_--;
    shrinkIfNeeded();
    return res;
}

template <typename T>
T ABDQ<T>::popBack() {
    if (size_ == 0) {
        throw std::runtime_error("Cannot pop empty dequeue");
    }
    T res = data_[p_dec(back_)];
    size_--;
    shrinkIfNeeded();
    return res;
}

// Access
template <typename T>
const T& ABDQ<T>::front() const {
    if (size_ == 0) {
        throw std::runtime_error("Cannot peek at empty dequeue");
    }
    return data_[front_];
}

template <typename T>
const T& ABDQ<T>::back() const {
    if (size_ == 0) {
        throw std::runtime_error("Cannot peek at empty dequeue");
    }
    return data_[(back_+capacity_-1)%capacity_]; // Cannot use p_dec(back_) here
}

template <typename T>
void ABDQ<T>::ensureCapacity() {
    if (size_ == capacity_) {
        T* new_data = new T[capacity_ * SCALE_FACTOR];
        for (size_t i = 0; i < size_; i++) {
            new_data[i] = data_[(i+front_)%capacity_];
        }
        delete[] data_;
        data_ = new_data;
        front_ = 0;
        back_ = size_;
        capacity_ *= SCALE_FACTOR;
    }
}

template <typename T>
void ABDQ<T>::shrinkIfNeeded() {
    if (size_ <= capacity_ / SCALE_FACTOR && size_ >= 4) {
        T* new_data = new T[capacity_ / SCALE_FACTOR];
        for (size_t i = 0; i < size_; i++) {
            new_data[i] = data_[(i+front_)%capacity_];
        }
        delete[] data_;
        data_ = new_data;
        front_ = 0;
        back_ = size_;
        capacity_ /= SCALE_FACTOR;
    }
};

// Big 5 + Parameterized Constructor
template <typename T>
ABDQ<T>::ABDQ() {
    capacity_ = 4;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[4];
};

template <typename T>
ABDQ<T>::ABDQ(const size_t capacity) {
    capacity_ = capacity;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity];
};

template <typename T>
ABDQ<T>::ABDQ(const ABDQ& other) {
    T* array = new T[other.capacity_];
    for (size_t i = other.front_; i != other.back_; other.p_inc(i)) {
        array[i] = other.data_[i];
    }
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = array;
    front_ = other.front_;
    back_ = other.back_;
};

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& rhs) {
    if (&rhs == this) return *this;
    T* array = new T[rhs.capacity_];
    for (size_t i = rhs.front_; i != rhs.back_; rhs.p_inc(i)) {
        array[i] = rhs.data_[i];
    }
    delete[] data_;
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_ = array;
    front_ = rhs.front_;
    back_ = rhs.back_;
    return *this;
};

template <typename T>
ABDQ<T>::ABDQ(ABDQ&& other) noexcept {
    capacity_ = other.capacity_;
    size_ = other.size_;
    data_ = other.data_;
    front_ = other.front_;
    back_ = other.back_;
    other.capacity_ = 0;
    other.size_ = 0;
    other.data_ = nullptr;
    other.front_ = 0;
    other.back_ = 0;
};

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ<T>&& rhs) noexcept {
    if (&rhs == this) return *this;
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_ = rhs.data_;
    front_ = rhs.front_;
    back_ = rhs.back_;
    rhs.capacity_ = 0;
    rhs.size_ = 0;
    rhs.data_ = nullptr;
    rhs.front_ = 0;
    rhs.back_ = 0;
    return *this;
};

template <typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
    front_ = 0;
    back_ = 0;
};