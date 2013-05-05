project(MintThreads)

file(GLOB INCFILES ../../include/mintthreads/*.h)
file(GLOB PRIVATE_INCFILES ../../include/mintthreads/private/*.h)
source_group("Header Files\\private" FILES ${PRIVATE_INCFILES})
include_directories(../../include)

if(${MSVC})
    file(GLOB SRCFILES msvc/*.c)
elseif(${UNIX})
    file(GLOB SRCFILES gcc/*.c)
endif()
add_library(MintThreads ${SRCFILES} ${INCFILES} ${PRIVATE_INCFILES})
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux requires linking with -lrt in order to call clock_getres from mint_timer_get.
    target_link_libraries(MintThreads rt)
endif()
include(../../cmake/BuildSettings.cmake)
