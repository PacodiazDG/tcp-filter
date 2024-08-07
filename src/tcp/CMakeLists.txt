

file(GLOB_RECURSE folder_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../toolkit/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../toolkit/*.h"
)


# Crea una biblioteca a partir de los archivos fuente
add_library(tcp_control SHARED ${folder_sources})
target_include_directories(tcp_control PUBLIC ${CMAKE_CURRENT_LIST_DIR})