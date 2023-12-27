cmake_minimum_required(VERSION 3.21)
project(virgo)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(CMAKE_VS_JUST_MY_CODE_DEBUGGING ON)

add_library(virgo STATIC include/Common/Span.h
        src/Common/Span.cpp
        include/Diagnostic/Diagnostic.h
        src/Parser/Lexer.cpp
        src/Common/Encoding.cpp
        include/Common/Encoding.h
        src/AST/Token.cpp
        include/Common/IO.h
        src/Common/IO.cpp
        include/Common/ByteLocation.h
        src/Common/ByteLocation.cpp
        include/Common/Error.h
        include/Diagnostic/DiagnosticsEmitter.h
        include/Diagnostic/Diagnostics.h
        src/Diagnostic/Diagnostics.cpp
        src/Diagnostic/DiagnosticsEmitter.cpp
        include/Common/Templates.h)
target_include_directories(virgo PUBLIC include)
target_include_directories(virgo PRIVATE src)
target_link_libraries(virgo ${llvm_libs})

enable_testing()
include(GoogleTest)

add_executable(virgo_exe src/main.cpp)
target_link_libraries(virgo_exe virgo)

function (declare_test name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} GTest::gtest_main virgo)
    gtest_discover_tests(${name})
endfunction()

declare_test(lexer_tests tests/Parser/Lexer.cpp)
declare_test(encoding_tests tests/Common/Encoding.cpp)
