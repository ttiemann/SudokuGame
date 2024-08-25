cmake_minimum_required(VERSION 3.8.0)
project(Sudoku VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the Qt6 libraries
set(CMAKE_PREFIX_PATH "/Users/Timo/Qt/6.7.2/macos")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON)

# Specify the source files
set(SOURCES
    main.cpp
    SudokuGrid.cpp
    SudokuWindow.cpp
)

# Specify the header files
set(HEADERS
    SudokuGrid.h
    SudokuWindow.h
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link Qt libraries to your project
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)  
