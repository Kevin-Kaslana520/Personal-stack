# MyStack — C++ Template Stack (installable)

这是一个小型的 C++ 模板栈实现，已经包含 CMake 安装与导出配置，克隆后可以直接构建并安装到系统或自定义前缀，然后在其他 CMake 项目中通过 `find_package()` 使用。

主要特性：
- 头文件式模板类：`include/MyStack/Stack.h`
- CMake 项目（最低 CMake 3.20）
- 提供示例（examples/）和测试（tests/）
- 已添加 `install()` 和 `install(EXPORT ...)`，可被 `find_package(MyStack)` 导入

快速开始

1. 克隆并构建并安装到默认前缀（例如 /usr/local）

```bash
git clone https://github.com/Kevin-Kaslana520/Personal-stack.git
cd Personal-stack
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target install
```

安装成功后，头文件会被安装到 `${CMAKE_INSTALL_PREFIX}/include/MyStack`，CMake 导出文件会被安装到 `${CMAKE_INSTALL_PREFIX}/lib/cmake/MyStack`。

2. 在其它 CMake 项目中使用（通过 find_package）

示例 CMakeLists.txt（在你自己的项目中）：

```cmake
cmake_minimum_required(VERSION 3.20)
project(YourApp LANGUAGES CXX)

find_package(MyStack 1.0 REQUIRED)

add_executable(YourApp src/main.cpp)
target_link_libraries(YourApp PRIVATE MyStack::MyStack)
```

然后在代码中包含头文件：

```c++
#include <MyStack/Stack.h>

int main() {
    MyStack::Stack<int> s(10);
    s.push(42);
    return 0;
}
```

如果你不想安装，也可以通过 `add_subdirectory()` 在上游工程中直接使用仓库：

```cmake
# 将 Personal-stack 仓库作为子目录
add_subdirectory(path/to/Personal-stack)

add_executable(YourApp src/main.cpp)
# MyStack 是 INTERFACE 目标，目标命名为 MyStack::MyStack（安装时使用的命名空间）
target_link_libraries(YourApp PRIVATE MyStack)
```

注意事项和建议

- CMake 最低版本：3.20（见 CMakeLists.txt）。
- 该库为模板实现（header + INTERFACE target），包含 `push/pop/top/isEmpty/isFull/print` 等基本操作。
- 异常行为：当栈满时 `push()` 抛出 `std::overflow_error`；当栈空时 `pop()`/`top()`/`print()` 抛出 `std::underflow_error` 。

建议（可选改进）

- 为 `Stack` 增加更完整的 API 文档（README 中的 API 说明或单独的 API 文档）。
- 将 `print()` 改为接收 `std::ostream&` 参数以便更灵活地输出（而不是直接写到 std::cout）。
- 增加更多单元测试（边界情况、移动语义、异常安全性测试等）。
- 若希望发布到包管理器（例如 vcpkg / Conan / package repository），可以添加 CPack/打包脚本或对应 port 配置。

如果你同意，我可以接下来：
- 1) 把 README 翻译并补充为更完整的英文使用说明并添加安装示例；
- 2) 修改 `Stack.h` 的 `print()` 签名以接受 `std::ostream&` 并更新示例和测试；
- 3) 添加一个简单的 CPack 打包配置（可选）。

请选择你要我接着做的改进（例如：修改 print()、增加 API 文档、添加 CPack、或其它）。
