
add_library(net STATIC bufconnection.cpp
                       epoll.cpp
                       option.cpp
                       service.cpp)
target_include_directories(net PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(net PUBLIC ${CMAKE_SOURCE_DIR}/2.LOG/include)
target_include_directories(net PUBLIC ${CMAKE_SOURCE_DIR}/3.TCP/include)
target_link_libraries(net log)
target_link_libraries(net tcp)
