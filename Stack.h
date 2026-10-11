#pragma once

#include <iostream>
#include <string>

#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class Stack
{
private:
	std::vector<T> arr;
	std::size_t capacity;
public:
	//初始化栈容量
	explicit Stack(std::size_t size) : capacity(size)
	{
		arr.reserve(capacity);
	}

	//操作函数
	//判断栈是否为空
	bool isEmpty() const
	{
		return arr.empty();
	}

	//判断栈是否已满
	bool isFull() const
	{
		return arr.size() == capacity;
	}

	//入栈操作
	void push(T value)
	{
		if (isFull())
		{
			throw std::overflow_error("Stack is full");
		}
		arr.push_back(std::move(value));
	}

	//出栈操作
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

	//获取栈顶元素	
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

	//打印栈内容
	void print() const
	{
		if (isEmpty())
		{
			throw std::underflow_error("Stack is empty");
		}
		std::cout << "Stack contents: ";
		for (const auto& value : arr)
		{
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

};
