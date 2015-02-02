if(CMAKE_SYSTEM_NAME MATCHES "AIX")
  foreach(step CREATE APPEND FINISH)
    string(REPLACE "<CMAKE_AR>" "<CMAKE_AR> -X64"
      CMAKE_CXX_ARCHIVE_${step} "${CMAKE_CXX_ARCHIVE_${step}}")
    string(REPLACE "<CMAKE_AR>" "<CMAKE_AR> -X64"
      CMAKE_C_ARCHIVE_${step} "${CMAKE_C_ARCHIVE_${step}}")
  endforeach()
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maix64")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maix64")
endif()

if(${MSVC})
    # Enable debug info in Release.
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Zi")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /debug")
elseif(${UNIX})
    # These are all required on Xcode 4.5.1 + iOS, because the defaults are no good.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
endif()


if(${IOS})
    set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
    set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
endif()
