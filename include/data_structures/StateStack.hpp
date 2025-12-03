#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <vector>
#include <stdexcept>

template<typename T>
class StateStack {
private:
    std::vector<T> stack;
    size_t maxSize;

public:
    StateStack(size_t max = 100) : maxSize(max) {}
    
    void push(const T& state);              // O(1) amortized
    T pop();                                // O(1)
    T peek() const;                         // O(1)
    void clear();                           // O(1)
    bool isEmpty() const { return stack.empty(); }
    size_t size() const { return stack.size(); }
    bool isFull() const { return stack.size() >= maxSize; }
};

// Template implementation

template<typename T>
void StateStack<T>::push(const T& state) {
    if (isFull()) {
        // Remove oldest state (bottom of stack)
        stack.erase(stack.begin());
    }
    stack.push_back(state);
}

template<typename T>
T StateStack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty!");
    }
    T state = stack.back();
    stack.pop_back();
    return state;
}

template<typename T>
T StateStack<T>::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty!");
    }
    return stack.back();
}

template<typename T>
void StateStack<T>::clear() {
    stack.clear();
}

#endif // STATE_STACK_HPP