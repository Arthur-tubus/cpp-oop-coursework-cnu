cmake_minimum_required(VERSION 3.15)

project(RestaurantManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Папка з хедерами
include_directories(include)

# Підключаємо всі cpp файли з src
file(GLOB SOURCES "src/*.cpp")

# Перевірка, що CMake знайшов файли
message(STATUS "Sources found: ${SOURCES}")

# Створюємо виконуваний файл
add_executable(MyProject ${SOURCES})

# Щоб exe був відразу в build/
set_target_properties(MyProject PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
