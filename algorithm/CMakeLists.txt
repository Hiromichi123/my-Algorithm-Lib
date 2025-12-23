cmake_minimum_required(VERSION 3.8)
project(algorithm)

set(CMAKE_CXX_STANDARD 17)           # 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 必须使用指定的标准
set(CMAKE_CXX_EXTENSIONS OFF)        # 禁用编译器特定的扩展

# 为对应编译器启用更严格的编译警告
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 基础编译包
find_package(ament_cmake REQUIRED)

# 可执行文件编译
add_executable(node1 grid_map.cpp)

# 可执行文件编译依赖
ament_target_dependencies(node1)
set(CMAKE_INSTALL_RPATH /usr/local/lib)

# 可执行文件安装
install(TARGETS node1 DESTINATION lib/${PROJECT_NAME})
ament_package()