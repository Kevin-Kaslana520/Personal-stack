#include <MyStack/Stack.h>
#include <iostream>


int main()
{
    MyStack::Stack<int> stack(5);

    stack.push(100);
    stack.push(200);

    std::cout << stack.top() << std::endl;

    return 0;
}