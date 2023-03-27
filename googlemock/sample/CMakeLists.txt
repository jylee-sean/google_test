cmake_minimum_required(VERSION 3.10)

# set the project name
project(MyTest)
set(CMAKE_CXX_STANDARD 14)

# locate and include the Google Test library
find_package(GTest REQUIRED)
SET(GTEST_INCLUDE_DIRS /usr/local/include)
include_directories(${GTEST_INCLUDE_DIRS})

# add the executable
SET(SRC_FILES test.cc)
add_executable(MyTest ${SRC_FILES})



SET(GTEST_LIBRARIES /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a /usr/local/lib/libgmock.a /usr/local/lib/libgmock_main.a)
# link the Google Test library
target_link_libraries(MyTest ${GTEST_LIBRARIES} pthread)

