include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.18.0/googletest-1.18.0.tar.gz
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_test
  unit/test_parser.cpp
)
target_link_libraries(unit_test PRIVATE
  shell-cpp-core
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_test)
