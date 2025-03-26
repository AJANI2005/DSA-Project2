cmake_minimum_required(VERSION 3.10)
project(wxWidgetsApp)

# Enable compilation database for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Enable necessary include/linking options
include(${wxWidgets_USE_FILE})

# Add include directory for header files
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/Visualizers)
include_directories(${CMAKE_SOURCE_DIR}/Tests)

# Add executable
add_executable(wxApp main.cpp)

# Link wxWidgets libraries
target_link_libraries(wxApp PRIVATE ${wxWidgets_LIBRARIES})


