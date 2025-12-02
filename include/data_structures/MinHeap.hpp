#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <vector>
#include <stdexcept>
#include <functional>
#include <iostream>

namespace DataStructures {

    /**
     * MinHeap Template Class
     * 
     * A generic min-heap implementation supporting any comparable type.
     * Used primarily for the triage priority queue system.
     * 
     * Time Complexities:
     * - insert(): O(log n)
     * - extractMin(): O(log n)
     * - getMin(): O(1)
     * - buildHeap(): O(n)
     * 
     * Space Complexity: O(n)
     */
    template<typename T>
    class MinHeap {
    protected:
        std::vector<T> heapArray;
        int heapSize;

        // Helper Methods
        int parent(int index) const { return (index - 1) / 2; }
        int leftChild(int index) const { return 2 * index + 1; }
        int rightChild(int index) const { return 2 * index + 2; }

        // Heapify Operations
        void heapifyUp(int index);
        void heapifyDown(int index);
        void swap(int i, int j);

    public:
        // Constructors
        MinHeap();
        MinHeap(const std::vector<T>& elements);
        MinHeap(const MinHeap<T>& other);
        
        // Destructor
        virtual ~MinHeap();

        // Assignment operator
        MinHeap<T>& operator=(const MinHeap<T>& other);

        // Core Operations - O(log n) insertion
        void insert(const T& item);
        
        // O(log n) extraction
        T extractMin();
        
        // O(1) peek
        T getMin() const;
        
        // O(n) build from array
        void buildHeap(const std::vector<T>& elements);

        // Utility Methods
        bool isEmpty() const { return heapSize == 0; }
        int size() const { return heapSize; }
        void clear();
        bool contains(const T& item) const;
        
        // Update priority of existing element - O(n) search + O(log n) heapify
        void updatePriority(const T& oldItem, const T& newItem);
        
        // Remove specific element - O(n) search + O(log n) heapify
        bool remove(const T& item);

        // Display Methods
        void display() const;
        std::vector<T> getElements() const { return heapArray; }
    };

    // ==================== IMPLEMENTATION ====================

    template<typename T>
    MinHeap<T>::MinHeap() : heapSize(0) {
        heapArray.clear();
    }

    template<typename T>
    MinHeap<T>::MinHeap(const std::vector<T>& elements) : heapSize(0) {
        buildHeap(elements);
    }

    template<typename T>
    MinHeap<T>::MinHeap(const MinHeap<T>& other) 
        : heapArray(other.heapArray), heapSize(other.heapSize) {}

    template<typename T>
    MinHeap<T>::~MinHeap() {
        clear();
    }

    template<typename T>
    MinHeap<T>& MinHeap<T>::operator=(const MinHeap<T>& other) {
        if (this != &other) {
            heapArray = other.heapArray;
            heapSize = other.heapSize;
        }
        return *this;
    }

    template<typename T>
    void MinHeap<T>::swap(int i, int j) {
        T temp = heapArray[i];
        heapArray[i] = heapArray[j];
        heapArray[j] = temp;
    }

    template<typename T>
    void MinHeap<T>::heapifyUp(int index) {
        while (index > 0 && heapArray[parent(index)] > heapArray[index]) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    template<typename T>
    void MinHeap<T>::heapifyDown(int index) {
        int minIndex = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heapSize && heapArray[left] < heapArray[minIndex]) {
            minIndex = left;
        }

        if (right < heapSize && heapArray[right] < heapArray[minIndex]) {
            minIndex = right;
        }

        if (minIndex != index) {
            swap(index, minIndex);
            heapifyDown(minIndex);
        }
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
            throw std::runtime_error("Heap is empty - cannot extract minimum");
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
            throw std::runtime_error("Heap is empty - no minimum element");
        }
        return heapArray[0];
    }

    template<typename T>
    void MinHeap<T>::buildHeap(const std::vector<T>& elements) {
        heapArray = elements;
        heapSize = elements.size();

        // Start from last non-leaf node and heapify down
        // O(n) amortized complexity
        for (int i = (heapSize / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    template<typename T>
    void MinHeap<T>::clear() {
        heapArray.clear();
        heapSize = 0;
    }

    template<typename T>
    bool MinHeap<T>::contains(const T& item) const {
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i] == item) {
                return true;
            }
        }
        return false;
    }

    template<typename T>
    void MinHeap<T>::updatePriority(const T& oldItem, const T& newItem) {
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i] == oldItem) {
                heapArray[i] = newItem;
                
                // Re-heapify based on whether priority increased or decreased
                if (newItem < oldItem) {
                    heapifyUp(i);
                } else {
                    heapifyDown(i);
                }
                return;
            }
        }
        throw std::runtime_error("Item not found in heap");
    }

    template<typename T>
    bool MinHeap<T>::remove(const T& item) {
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i] == item) {
                // Replace with last element and remove
                heapArray[i] = heapArray[heapSize - 1];
                heapArray.pop_back();
                heapSize--;

                if (i < heapSize) {
                    heapifyDown(i);
                    heapifyUp(i);
                }
                return true;
            }
        }
        return false;
    }

    template<typename T>
    void MinHeap<T>::display() const {
        std::cout << "Heap [size=" << heapSize << "]: ";
        for (int i = 0; i < heapSize; i++) {
            std::cout << heapArray[i] << " ";
        }
        std::cout << std::endl;
    }

} // namespace DataStructures

#endif // MIN_HEAP_HPP