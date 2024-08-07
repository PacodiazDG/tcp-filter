

file(GLOB_RECURSE folder_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"

     




)
# Crea una biblioteca a partir de los archivos fuente
add_library(toolkit SHARED ${folder_sources})
target_include_directories(toolkit PUBLIC ${CMAKE_CURRENT_LIST_DIR})