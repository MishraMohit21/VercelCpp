cmake_minimum_required(VERSION 3.5)
project(VercelDeployService CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(Drogon REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(HIREDIS REQUIRED hiredis)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)

# Include directories
include_directories(${LIBGIT2_INCLUDE_DIRS} ${HIREDIS_INCLUDE_DIRS})

# Add source files
add_executable(${PROJECT_NAME} src/main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Drogon::Drogon
    ${LIBGIT2_LIBRARIES}
    ${HIREDIS_LIBRARIES}
)
