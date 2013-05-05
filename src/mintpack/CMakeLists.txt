project(MintPack)

file(GLOB SRCFILES *.cpp)
file(GLOB INCFILES ../../include/mintpack/*.h)
add_library(MintPack ${SRCFILES} ${INCFILES})
include(../../cmake/BuildSettings.cmake)
