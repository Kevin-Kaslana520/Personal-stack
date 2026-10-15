#pragma once

#include <iostream>
#include <string>

#include <stdexcept>
#include <utility>
#include <vector>
namespace MyStack
{
    template <typename T>
    class Stack
    {
    private:
        std::vector<T> arr;
        std::size_t capacity;
    public:
        // initialize stack capacity
        explicit Stack(std::size_t size) : capacity(size)
        {
            if (capacity == 0)
            {
                throw std::invalid_argument("Stack capacity must be greater than zero");
            }
            arr.reserve(capacity);
        }

        // operations
        // is empty
        bool isEmpty() const
        {
            return arr.empty();
        }

        // is full
        bool isFull() const
        {
            return arr.size() == capacity;
        }

        // push
        void push(T value)
        {
            if (isFull())
            {
                throw std::overflow_error("Stack is full");
            }
            arr.push_back(std::move(value));
        }

        // pop
        T pop()
        {
            if (isEmpty())
            {
                throw std::underflow_error("Stack is empty");
            }
            T value = std::move(arr.back());
            arr.pop_back();
            return value;
        }

        // top
        T& top()
        {
            if (isEmpty())
            {
                throw std::underflow_error("Stack is empty");
            }
            return arr.back();
        }

        const T& top() const
        {
            if (isEmpty())
            {
                throw std::underflow_error("Stack is empty");
            }
            return arr.back();
        }

        // print stack contents to provided ostream (default: std::cout)
        void print(std::ostream& os = std::cout) const
        {
            if (isEmpty())
            {
                throw std::underflow_error("Stack is empty");
            }
            os << "Stack contents: ";
            for (const auto& value : arr)
            {
                os << value << " ";
            }
            os << std::endl;
        }

    };
}
