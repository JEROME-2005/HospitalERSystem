// include/data_structures/StateStack.hpp
#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include "../utils/CommonTypes.hpp"

namespace HEROS {
namespace DataStructures {

/**
 * StateStack - Generic Stack for Undo/Redo Operations
 * 
 * Time Complexity:
 *   - push():  O(1) amortized
 *   - pop():   O(1)
 *   - peek():  O(1)
 * 
 * Space Complexity: O(m) where m = max undo steps
 */
template<typename T>
class StateStack {
private:
    std::vector<T> stack;
    size_t maxSize;

public:
    // Constructors
    StateStack(size_t max = 100) : maxSize(max) {}
    
    // Destructor
    ~StateStack() = default;
    
    // Core stack operations
    void push(const T& state) {
        if (stack.size() >= maxSize) {
            // Remove oldest state to make room
            stack.erase(stack.begin());
        }
        stack.push_back(state);
    }
    
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty - cannot pop");
        }
        T top = stack.back();
        stack.pop_back();
        return top;
    }
    
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty - cannot peek");
        }
        return stack.back();
    }
    
    // Utility
    void clear() { stack.clear(); }
    bool isEmpty() const { return stack.empty(); }
    size_t size() const { return stack.size(); }
    size_t getMaxSize() const { return maxSize; }
    void setMaxSize(size_t max) { maxSize = max; }
    
    // Access all states (for debugging)
    std::vector<T> getAllStates() const { return stack; }
};

} // namespace DataStructures
} // namespace HEROS

#endif // STATE_STACK_HPP