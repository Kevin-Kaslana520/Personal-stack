#include <MyStack/Stack.h>
#include <iostream>
using MyStack::Stack;
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
	bool allExceptionsPassed = true;
	auto report = [&allExceptionsPassed](const char* operation, bool passed)
	{
		std::cout << (passed ? "通过：" : "失败：") << operation << std::endl;
		if (!passed)
		{
			allExceptionsPassed = false;
		}
	};

	Stack<int> fullStack(1);
	fullStack.push(100);
	bool overflowThrown = false;
	try
	{
		fullStack.push(200);
	}
	catch (const std::overflow_error&)
	{
		overflowThrown = true;
	}
	report("栈满时 push() 抛出 std::overflow_error", overflowThrown);

	Stack<int> emptyStack(1);
	bool popUnderflowThrown = false;
	try
	{
		emptyStack.pop();
	}
	catch (const std::underflow_error&)
	{
		popUnderflowThrown = true;
	}
	report("空栈时 pop() 抛出 std::underflow_error", popUnderflowThrown);

	bool topUnderflowThrown = false;
	try
	{
		emptyStack.top();
	}
	catch (const std::underflow_error&)
	{
		topUnderflowThrown = true;
	}
	report("空栈时 top() 抛出 std::underflow_error", topUnderflowThrown);

	bool printUnderflowThrown = false;
	try
	{
		emptyStack.print();
	}
	catch (const std::underflow_error&)
	{
		printUnderflowThrown = true;
	}
	report("空栈时 print() 抛出 std::underflow_error", printUnderflowThrown);

	return allExceptionsPassed ? 0 : 1;
}

