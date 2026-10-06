cmake_minimum_required(VERSION 3.20)     #指定cmake的最低版本（必须放在最前面）
project(engineering)         #定义项目名称、版本和语言
set(CMAKE_CXX_STANDARD 20)     #设置C++标准为C++20，并强制要求使用该标准

add_executable(todolist todo_list.cpp)      #添加可执行文件目标
add_executable(test test.cpp)

target_compile_options(todolist PRIVATE
        -finput-charset=UTF-8
        -fexec-charset=UTF-8
)

