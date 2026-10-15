cmake_minimum_required(VERSION 3.20)

project(MyStack VERSION 1.0.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Build the library as a header-only interface target.
add_library(MyStack INTERFACE)
add_library(MyStack::MyStack ALIAS MyStack)
set_target_properties(MyStack PROPERTIES EXPORT_NAME MyStack)

target_include_directories(MyStack INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(MyStack INTERFACE cxx_std_17)

# Example executable.
add_executable(MyStackExample
    examples/main.cpp
)

target_link_libraries(MyStackExample PRIVATE MyStack)
target_compile_features(MyStackExample PRIVATE cxx_std_17)

# Unit tests.
include(CTest)
if(BUILD_TESTING)
    add_executable(StackTests
        tests/StackTest.cpp
    )

    target_link_libraries(StackTests PRIVATE MyStack)
    target_compile_features(StackTests PRIVATE cxx_std_17)

    add_test(NAME StackTests COMMAND StackTests)
endif()

# Install headers.
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the library target and its package export.
install(
    TARGETS MyStack
    EXPORT MyStackTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT MyStackTargets
    FILE MyStackTargets.cmake
    NAMESPACE MyStack::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyStack
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/MyStackConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MyStackConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyStack
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MyStackConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MyStackConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MyStackConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyStack
)

include(CPack)
