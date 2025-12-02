// include/data_structures/MinHeap.hpp
#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include "../utils/CommonTypes.hpp"

namespace HEROS {
namespace DataStructures {

/**
 * MinHeap - Generic Min Heap Implementation
 * 
 * Time Complexity:
 *   - insert():      O(log n)
 *   - extractMin():  O(log n)
 *   - getMin():      O(1)
 *   - buildHeap():   O(n)
 * 
 * Space Complexity: O(n)
 */
template<typename T>
class MinHeap {
protected:
    std::vector<T> heapArray;
    
    // Helper functions for index calculations
    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }
    
    // Heapify operations
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);
    
public:
    // Constructors
    MinHeap() = default;
    MinHeap(const std::vector<T>& elements);
    
    // Destructor
    virtual ~MinHeap() = default;
    
    // Core operations
    void insert(const T& item);           // O(log n)
    T extractMin();                        // O(log n)
    T getMin() const;                      // O(1)
    
    // Utility operations
    bool isEmpty() const { return heapArray.empty(); }
    int size() const { return static_cast<int>(heapArray.size()); }
    void clear() { heapArray.clear(); }
    void buildHeap(const std::vector<T>& elements);  // O(n)
    
    // Access to underlying data
    std::vector<T> getAllElements() const { return heapArray; }
    
    // Debug/Visualization
    void printHeap() const;
    bool isValidHeap() const;
};

// ============== IMPLEMENTATION ==============

template<typename T>
MinHeap<T>::MinHeap(const std::vector<T>& elements) {
    buildHeap(elements);
}

template<typename T>
void MinHeap<T>::swap(int i, int j) {
    T temp = heapArray[i];
    heapArray[i] = heapArray[j];
    heapArray[j] = temp;
}

template<typename T>
void MinHeap<T>::heapifyUp(int index) {
    // Move element up while it's smaller than parent
    while (index > 0 && heapArray[index] < heapArray[parent(index)]) {
        swap(index, parent(index));
        index = parent(index);
    }
}

template<typename T>
void MinHeap<T>::heapifyDown(int index) {
    int minIndex = index;
    int n = size();
    
    int left = leftChild(index);
    if (left < n && heapArray[left] < heapArray[minIndex]) {
        minIndex = left;
    }
    
    int right = rightChild(index);
    if (right < n && heapArray[right] < heapArray[minIndex]) {
        minIndex = right;
    }
    
    if (minIndex != index) {
        swap(index, minIndex);
        heapifyDown(minIndex);
    }
}

template<typename T>
void MinHeap<T>::insert(const T& item) {
    // Add element to end and heapify up
    heapArray.push_back(item);
    heapifyUp(size() - 1);
}

template<typename T>
T MinHeap<T>::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty - cannot extract minimum");
    }
    
    T minElement = heapArray[0];
    
    // Move last element to root and heapify down
    heapArray[0] = heapArray.back();
    heapArray.pop_back();
    
    if (!isEmpty()) {
        heapifyDown(0);
    }
    
    return minElement;
}

template<typename T>
T MinHeap<T>::getMin() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty - no minimum element");
    }
    return heapArray[0];
}

template<typename T>
void MinHeap<T>::buildHeap(const std::vector<T>& elements) {
    heapArray = elements;
    
    // Build heap in O(n) by starting from last non-leaf node
    for (int i = size() / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

template<typename T>
void MinHeap<T>::printHeap() const {
    std::cout << "Heap contents (" << size() << " elements): [";
    for (size_t i = 0; i < heapArray.size(); ++i) {
        std::cout << heapArray[i];
        if (i < heapArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

template<typename T>
bool MinHeap<T>::isValidHeap() const {
    for (int i = 0; i < size(); ++i) {
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < size() && heapArray[left] < heapArray[i]) {
            return false;
        }
        if (right < size() && heapArray[right] < heapArray[i]) {
            return false;
        }
    }
    return true;
}

} // namespace DataStructures
} // namespace HEROS

#endif // MIN_HEAP_HPP