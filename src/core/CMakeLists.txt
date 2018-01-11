add_library(image image.cpp)
target_link_libraries(image nlohmann_json libcurl)
target_include_directories(image PUBLIC ${HEADER_LIST})
