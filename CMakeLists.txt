cmake_minimum_required (VERSION 3.19.2)
if(DEFINED CLANG_LINK_DIRECTORIES)
    link_directories(BEFORE ${CLANG_LINK_DIRECTORIES})
endif()

project (a.out)
find_package(Threads REQUIRED)
#SET(BOOST_ROOT "/usr/local/Cellar/boost/1.61.0")
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${BOOST_ROOT}/include)
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${BOOST_ROOT}/lib)
include_directories(SYSTEM /usr/local/include)
find_package(Boost 1.75.0
    COMPONENTS
        atomic
        chrono
        container
        context
        coroutine
        date_time
        exception
        filesystem
        graph
        iostreams
        locale
        log
        log_setup
        math_c99
        math_c99f
        math_c99l
        math_tr1
        math_tr1f
        math_tr1l
        prg_exec_monitor
        program_options
        #python
        random
        regex
        serialization
        #signals
        system
        test_exec_monitor
        thread
        timer
        unit_test_framework
        wave
        wserialization
    REQUIRED)
link_directories(AFTER "/usr/local/opt/icu4c/lib/") # for Boost.Regex on 1.75
add_executable(${PROJECT_NAME} a.cpp main.cpp)
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

set(MAKE_EXPORT_COMPILE_COMMANDS ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
    elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
    endif()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
    endif()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
endif()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")


# Sanitizers
set(CMAKE_CXX_SANITIZER_FLAGS "${CMAKE_CXX_SANITIZER_FLAGS} -fsanitize=undefined")
set(CMAKE_CXX_SANITIZER_FLAGS "${CMAKE_CXX_SANITIZER_FLAGS} -fsanitize=address")
#set(CMAKE_CXX_SANITIZER_FLAGS "${CMAKE_CXX_SANITIZER_FLAGS} -fsanitize=thread")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_SANITIZER_FLAGS}")

if(APPLE)
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -stdlib=libc++")
endif(APPLE)

if(UNIX AND NOT APPLE)
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -stdlib=libstdc++")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} --gcc-toolchain=/usr/local/gcc")
endif(UNIX AND NOT APPLE)

set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Weverything")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Wno-c++98-compat")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Wno-c++98-compat-pedantic")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Wno-poison-system-directories")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Wno-padded")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Wno-date-time")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Wno-unused-member-function")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Wno-reserved-id-macro")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -Wno-undefined-func-template")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -fcolor-diagnostics")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -fdiagnostics-format=vi")
set(CMAKE_CXX_CLANG_FLAGS "${CMAKE_CXX_CLANG_FLAGS} -fdiagnostics-show-category=name")

set(CMAKE_CXX_GNU_FLAGS "${CMAKE_CXX_GNU_FLAGS} -Wall")
set(CMAKE_CXX_GNU_FLAGS "${CMAKE_CXX_GNU_FLAGS} -Wextra")
set(CMAKE_CXX_GNU_FLAGS "${CMAKE_CXX_GNU_FLAGS} -Wno-unused-local-typedefs")
set(CMAKE_CXX_GNU_FLAGS "${CMAKE_CXX_GNU_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_CXX_GNU_FLAGS "${CMAKE_CXX_GNU_FLAGS} -fdiagnostics-color")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_CLANG_FLAGS}")
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_GNU_FLAGS}")
endif()

