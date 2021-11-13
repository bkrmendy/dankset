project(tests)

add_subdirectory(thirdparty/googletest)
include_directories(../lib ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(thirdparty/rapidcheck)
add_subdirectory(thirdparty/rapidcheck/extras/gtest)

add_executable(tests src/main.cpp src/unit_hashset.cpp src/rc_hashset.cpp)
target_link_libraries(tests hashset gtest gtest_main gmock gmock_main rapidcheck rapidcheck_gtest)