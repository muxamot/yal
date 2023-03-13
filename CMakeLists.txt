cmake_minimum_required(VERSION 3.10)

project(yaL)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed")
endif()

set (EMS_LINKER_FLAGS -sLLD_REPORT_UNDEFINED)
set (EMS_COMMON_FLAGS -fexceptions -sUSE_SDL=2 -sUSE_BOOST_HEADERS=1)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(YAL_SRC
  src/event_loop.cpp  
  src/main.cpp
  src/window.cpp
)

add_executable(yal ${YAL_SRC})
target_compile_options(yal PRIVATE -fexperimental-library ${EMS_COMMON_FLAGS})
target_link_options(yal PRIVATE ${EMS_COMMON_FLAGS} ${EMS_LINKER_FLAGS})
# looks like boost from emscripten-ports will fail to build on C++17 and this is sad
set_property(TARGET yal PROPERTY CXX_STANDARD 20)

# SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(yal PUBLIC SDL2)

include_directories(yal ${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(yal ${SDL2_INCLUDE_DIRS})
include_directories(yal ${BOOST_INCLUDE_DIRS})