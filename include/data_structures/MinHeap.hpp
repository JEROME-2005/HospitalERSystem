#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

template<typename T>
class MinHeap {
private:
    std::vector<T> heapArray;
    int heapSize;
    
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }
    
    void heapifyDown(int index);
    void heapifyUp(int index);

public:
    MinHeap();
    
    void insert(const T& item);
    T extractMin();
    T getMin() const;
    bool isEmpty() const { return heapSize == 0; }
    int size() const { return heapSize; }
    void buildHeap(const std::vector<T>& elements);
    void clear() { heapArray.clear(); heapSize = 0; }
    
    void display() const;
    const std::vector<T>& getHeapArray() const { return heapArray; }
};

template<typename T>
MinHeap<T>::MinHeap() : heapSize(0) {
    heapArray.reserve(100);
}

template<typename T>
void MinHeap<T>::insert(const T& item) {
    heapArray.push_back(item);
    heapSize++;
    heapifyUp(heapSize - 1);
}

template<typename T>
T MinHeap<T>::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty!");
    }
    
    T minItem = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapArray.pop_back();
    heapSize--;
    
    if (!isEmpty()) {
        heapifyDown(0);
    }
    
    return minItem;
}

template<typename T>
T MinHeap<T>::getMin() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty!");
    }
    return heapArray[0];
}

template<typename T>
void MinHeap<T>::heapifyDown(int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < heapSize && heapArray[left] < heapArray[smallest]) {
        smallest = left;
    }
    
    if (right < heapSize && heapArray[right] < heapArray[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        std::swap(heapArray[index], heapArray[smallest]);
        heapifyDown(smallest);
    }
}

template<typename T>
void MinHeap<T>::heapifyUp(int index) {
    if (index == 0) return;
    
    int parentIdx = parent(index);
    
    if (heapArray[index] < heapArray[parentIdx]) {
        std::swap(heapArray[index], heapArray[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template<typename T>
void MinHeap<T>::buildHeap(const std::vector<T>& elements) {
    heapArray = elements;
    heapSize = elements.size();
    
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

template<typename T>
void MinHeap<T>::display() const {
    std::cout << "Heap contents (" << heapSize << " elements): ";
    for (int i = 0; i < heapSize; i++) {
        std::cout << heapArray[i] << " ";
    }
    std::cout << std::endl;
}

#endif