#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

namespace DataStructures {

    /**
     * StateStack Template Class
     * 
     * A generic stack implementation for undo/redo functionality.
     * Stores state snapshots for reverting operations.
     * 
     * Time Complexities:
     * - push(): O(1) amortized
     * - pop(): O(1)
     * - peek(): O(1)
     * 
     * Space Complexity: O(m) where m is max history size
     */
    template<typename T>
    class StateStack {
    private:
        std::vector<T> stack;
        size_t maxSize;
        size_t currentSize;

    public:
        // Constructors
        StateStack(size_t maxHistorySize = 100);
        StateStack(const StateStack<T>& other);
        
        // Destructor
        ~StateStack();

        // Assignment operator
        StateStack<T>& operator=(const StateStack<T>& other);

        // Core Stack Operations
        void push(const T& state);
        T pop();
        T peek() const;
        
        // Utility Methods
        bool isEmpty() const { return currentSize == 0; }
        bool isFull() const { return currentSize >= maxSize; }
        size_t size() const { return currentSize; }
        size_t capacity() const { return maxSize; }
        void clear();
        void resize(size_t newMaxSize);
        
        // Access Methods
        T getAt(size_t index) const;
        std::vector<T> getAllStates() const { return stack; }
        
        // Display
        void display() const;
    };

    // ==================== IMPLEMENTATION ====================

    template<typename T>
    StateStack<T>::StateStack(size_t maxHistorySize) 
        : maxSize(maxHistorySize), currentSize(0) {
        stack.reserve(maxHistorySize);
    }

    template<typename T>
    StateStack<T>::StateStack(const StateStack<T>& other)
        : stack(other.stack), maxSize(other.maxSize), currentSize(other.currentSize) {}

    template<typename T>
    StateStack<T>::~StateStack() {
        clear();
    }

    template<typename T>
    StateStack<T>& StateStack<T>::operator=(const StateStack<T>& other) {
        if (this != &other) {
            stack = other.stack;
            maxSize = other.maxSize;
            currentSize = other.currentSize;
        }
        return *this;
    }

    template<typename T>
    void StateStack<T>::push(const T& state) {
        if (currentSize >= maxSize) {
            // Remove oldest state (front of vector) to maintain max size
            stack.erase(stack.begin());
            currentSize--;
        }
        stack.push_back(state);
        currentSize++;
    }

    template<typename T>
    T StateStack<T>::pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty - cannot pop");
        }
        T topState = stack.back();
        stack.pop_back();
        currentSize--;
        return topState;
    }

    template<typename T>
    T StateStack<T>::peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty - cannot peek");
        }
        return stack.back();
    }

    template<typename T>
    void StateStack<T>::clear() {
        stack.clear();
        currentSize = 0;
    }

    template<typename T>
    void StateStack<T>::resize(size_t newMaxSize) {
        maxSize = newMaxSize;
        while (currentSize > maxSize) {
            stack.erase(stack.begin());
            currentSize--;
        }
    }

    template<typename T>
    T StateStack<T>::getAt(size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return stack[index];
    }

    template<typename T>
    void StateStack<T>::display() const {
        std::cout << "StateStack [size=" << currentSize << "/" << maxSize << "]" << std::endl;
        for (size_t i = currentSize; i > 0; i--) {
            std::cout << "  [" << (currentSize - i) << "] " << stack[i-1] << std::endl;
        }
    }

} // namespace DataStructures

#endif // STATE_STACK_HPP