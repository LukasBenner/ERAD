add_executable(erad_test erad_test.cpp)
target_link_libraries(erad_test PRIVATE erad_lib)


AddTests(erad_test)