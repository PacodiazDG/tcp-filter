

file(GLOB_RECURSE folder_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../tls/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../tls/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../tcp/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../tcp/*.h"
)
# Crea una biblioteca a partir de los archivos fuente
add_library(nfqueue_control SHARED ${folder_sources})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNETFILTER_QUEUE REQUIRED libnetfilter_queue)
include_directories(${LIBNETFILTER_QUEUE_INCLUDE_DIRS})
link_directories(${LIBNETFILTER_QUEUE_LIBRARY_DIRS})
target_include_directories(nfqueue_control PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(nfqueue_control PRIVATE ${LIBNETFILTER_QUEUE_LIBRARIES})