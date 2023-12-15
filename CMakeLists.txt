cmake_minimum_required(VERSION 3.26)
project(virgo)

set(CMAKE_CXX_STANDARD 17)

add_library(virgo STATIC include/Common/Span.h src/Common/Span.cpp
        include/Diagnostic/Diagnostic.h
        src/Diagnostic/Diagnostic.cpp
        include/Intern/XXHash.h
        include/Intern/XXHash.h)
target_include_directories(virgo PUBLIC include)
target_include_directories(virgo PRIVATE src)
target_sources(virgo
        PUBLIC
        include/Common/Span.h
        PRIVATE
        src/Common/Span.cpp
)

add_executable(virgo_cli src/main.cpp)
target_link_libraries(virgo_cli virgo)
