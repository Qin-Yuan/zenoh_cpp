cmake_minimum_required(VERSION 3.16)
project(pub LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

find_package(zenohc)
find_package(zenohcxx)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(pub_demo src/pub_demo.cpp)
target_link_libraries(pub_demo PRIVATE zenohcxx::zenohc::lib)

add_executable(sub_demo src/sub_demo.cpp)
target_link_libraries(sub_demo PRIVATE zenohcxx::zenohc::lib)

add_executable(pub_cv2 src/pub_cv2.cpp)
target_link_libraries(pub_cv2 PRIVATE zenohcxx::zenohc::lib ${OpenCV_LIBS} nlohmann_json::nlohmann_json)

add_executable(sub_cv2 src/sub_cv2.cpp)
target_link_libraries(sub_cv2 PRIVATE zenohcxx::zenohc::lib ${OpenCV_LIBS} nlohmann_json::nlohmann_json)
