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
int main()
{
	auto testStack = [](const char* typeName, auto first, auto second, auto overflow)
	{
		Stack<decltype(first)> stack(2);
		std::cout << "\n测试 " << typeName << " 类型栈：" << std::endl;
		try
		{
			stack.push(first);
			stack.push(second);
			stack.push(overflow);
		}
		catch (const std::overflow_error& error)
		{
			std::cout << "捕获栈满异常: " << error.what() << std::endl;
		}

		stack.print();
		std::cout << "栈顶元素: " << stack.top() << std::endl;

		for (int i = 0; i < 2; ++i)
		{
			std::cout << "出栈元素: " << stack.pop() << std::endl;
		}

		try
		{
			stack.pop();
		}
		catch (const std::underflow_error& error)
		{
			std::cout << "捕获空栈出栈异常: " << error.what() << std::endl;
		}

		try
		{
			stack.top();
		}
		catch (const std::underflow_error& error)
		{
			std::cout << "捕获空栈取栈顶异常: " << error.what() << std::endl;
		}

		try
		{
			stack.print();
		}
		catch (const std::underflow_error& error)
		{
			std::cout << "捕获空栈打印异常: " << error.what() << std::endl;
		}
	};

	testStack("int", 10, 20, 30);
	testStack("double", 1.5, 2.5, 3.5);
	testStack("string", std::string("hello"), std::string("world"), std::string("stack full"));

    return 0;

}

