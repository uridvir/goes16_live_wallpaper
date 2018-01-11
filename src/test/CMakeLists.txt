add_executable(image_test image_test.cpp)
target_link_libraries(image_test image gtest)
add_test(NAME image COMMAND image_test)
