#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <utility>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS();

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;

	void printForward() const;
	void printReverse() const;
};

template <typename T>
LLS<T>::LLS() : list() {}

template <typename T>
void LLS<T>::push(const T& item) {
    list.addHead(item);
}

template <typename T>
T LLS<T>::pop() {
    if (list.getCount() == 0) {
        throw std::runtime_error("cannot pop empty stack");
    }
    T res = list.getHead()->data;
    list.removeHead();
    return res;
};

template <typename T>
T LLS<T>::peek() const {
    if (list.getCount() == 0) {
        throw std::runtime_error("cannot peek at empty stack");
    }
    return list.getHead()->data;
};

template <typename T>
std::size_t LLS<T>::getSize() const noexcept {
    return list.getCount();
}

template <typename T>
void LLS<T>::printForward() const {
    list.printForward();
}

template <typename T>
void LLS<T>::printReverse() const {
    list.printReverse();
}