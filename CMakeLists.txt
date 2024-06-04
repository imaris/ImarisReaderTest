cmake_minimum_required(VERSION 3.29)

project(ImarisReaderTest)

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

set(CMAKE_C_STANDARD   99)
set(CMAKE_CXX_STANDARD 11)
enable_language(CXX)

add_library(bpImarisReader SHARED IMPORTED)
if(CMAKE_SYSTEM_NAME MATCHES Windows)
    set_property(TARGET bpImarisReader PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/bpImarisReader.dll)
elseif(CMAKE_SYSTEM_NAME MATCHES Darwin)
    set_property(TARGET bpImarisReader PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libbpImarisReader.dylib)
endif()
#set_source_files_properties(cReaderTest.c PROPERTIES LANGUAGE CXX)
add_executable(ImarisReaderTest cppReaderTest.cpp)
target_link_libraries(ImarisReaderTest bpImarisReader)
