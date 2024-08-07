cmake_minimum_required(VERSION 3.22.1)
project(tcpnfqfilter)
add_subdirectory(nfqueue)
add_subdirectory(tcp)
add_subdirectory(tls)
add_subdirectory(toolkit)
set(libs
nfqueue_control
tcp_control
tls_control
toolkit
curl
)
target_link_libraries(nfqueue_control)
target_link_libraries(tcp_control)
target_link_libraries(tls_control)
target_link_libraries(toolkit)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED) 
add_executable(tcpnfqfilter main.cpp)
find_library(NFNETLINK_LIBRARY nfnetlink)
find_library(NETFILTER_QUEUE_LIBRARY netfilter_queue)
find_library(NETFILTER_QUEUE_LIBRARY netfilter_queue)

 
set( tcpnfqfilter   "-fstack-protector -fstack-protector-all -D_FORTIFY_SOURCE=2 -Wl,-z,noexecstack	-Wl,-z,now" )
target_link_libraries(tcpnfqfilter  ${NFNETLINK_LIBRARY} ${NETFILTER_QUEUE_LIBRARY} ${NETFILTER_QUEUE_LIBRARY} ${libs}  OpenSSL::SSL OpenSSL::Crypto )