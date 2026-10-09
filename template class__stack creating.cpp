#include <iostream>

class Stack
{
private:
	int* arr;
	int capacity;
	int top;
public:
	//分配内存，初始化栈顶指针为0
	Stack(int size) :capacity(size), top(0)
	{
		arr = new int[capacity];
	}

	//析构函数释放内存
	~Stack()
	{
		delete[] arr;
		arr = nullptr;
	}

	//操作函数
	//判断栈是否为空
	bool isEmpty() const
	{
		return top == 0;
	}

	//判断栈是否已满
	bool isFull() const
	{
		return top == capacity;
	}

	//入栈操作
	void push(int value)
	{
		if (isFull())
		{
			std::cout << "Stack is full. Cannot push " << value << std::endl;
			return;
		}
		arr[top++] = value;
	}
	
	//出栈操作
	int pop()
	{
		if (isEmpty())
		{
			std::cout << "Stack is empty. Cannot pop." << std::endl;
			return -1; // Return a sentinel value to indicate an error
		}
		return arr[--top];
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
		for (int i = 0; i < top; ++i)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}

};
int main()
{
    Stack s(5);
    s.push(10);
    s.push(20);
    s.push(30);
	s.print();
	while (!s.isEmpty())
	{
		std::cout << "Popped: " << s.pop() << std::endl;
	};
    s.print();
    return 0;

}

