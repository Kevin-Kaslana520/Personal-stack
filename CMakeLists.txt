
cmake_minimum_required(VERSION 3.20)

project(MyStack LANGUAGES CXX)


# 创建 MyStack 库
add_library(MyStack INTERFACE)

target_include_directories(MyStack INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 创建测试程序
add_executable(StackTests
    tests/StackTest.cpp
)


# 测试程序使用 MyStack
target_link_libraries(StackTests PRIVATE
    MyStack
)


target_compile_features(StackTests PRIVATE cxx_std_17)

add_executable(MyStackExample
    examples/main.cpp
)

target_link_libraries(MyStackExample PRIVATE
    MyStack
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    TARGETS MyStack
    EXPORT MyStackTargets
)

include(CMakePackageConfigHelpers)


write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MyStackConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)


configure_package_config_file(
    cmake/MyStackConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MyStackConfig.cmake"
    INSTALL_DESTINATION lib/cmake/MyStack
)


install(
    EXPORT MyStackTargets
    FILE MyStackTargets.cmake
    NAMESPACE MyStack::
    DESTINATION lib/cmake/MyStack
)


install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/MyStackConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/MyStackConfigVersion.cmake"
    DESTINATION lib/cmake/MyStack
)