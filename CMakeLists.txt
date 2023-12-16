cmake_minimum_required(VERSION 3.26)
project(virgo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(CMAKE_VS_JUST_MY_CODE_DEBUGGING ON)

add_library(virgo STATIC include/Common/Span.h
        include/Diagnostic/Diagnostic.h
        src/Parser/Lexer.cpp
        src/Parser/Lexer.cpp
        src/Parser/Lexer.cpp
        src/Common/CodePointsIterator.cpp
        include/Common/Encoding.h
        src/AST/Token.cpp)
target_include_directories(virgo PUBLIC include)
target_include_directories(virgo PRIVATE src)
target_link_libraries(virgo ${llvm_libs})

add_executable(virgo_exe src/main.cpp)
target_link_libraries(virgo_exe virgo)
