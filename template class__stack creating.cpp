#include <iostream>
#include <optional>
#include <string>
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
	bool push(T value)
	{
		if (isFull())
		{
			return false;
		}
		arr.push_back(std::move(value));
		return true;
	}
	
	//出栈操作
	std::optional<T> pop()
	{
		if (isEmpty())
		{
			return std::nullopt;
		}
		T value = std::move(arr.back());
		arr.pop_back();
		return value;
	}

	//打印栈内容
	void print() const
	{
		if (isEmpty())
		{
			std::cout << "Stack is empty." << std::endl;
			return;
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
	Stack<int> intStack(5);
	intStack.push(10);
	intStack.push(20);
	intStack.print();
	while (const auto value = intStack.pop())
	{
		std::cout << "Popped: " << *value << std::endl;
	}

	Stack<std::string> stringStack(2);
	stringStack.push("hello");
	stringStack.push("world");
	stringStack.print();

    return 0;

}

