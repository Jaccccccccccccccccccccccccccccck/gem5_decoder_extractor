cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ext/pybind11)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories(/usr/include)
include_directories(./)
include_directories(include)
include_directories(ext)
include_directories(ext/pybind11)
include_directories(ext/pybind11/include)
include_directories(ext/pybind11/include/pybind11)
include_directories(ext/libfdt)
include_directories(ext/iostream3)
include_directories(ext/dsent)
include_directories(ext/drampower)
include_directories(ext/drampower/src)
include_directories(ext/nomali/include)
include_directories(ext/libelf/include)
include_directories(ext/googletest/googlemock)
include_directories(ext/googletest/googletest)
include_directories(ext/googletest/googlemock/include)
include_directories(ext/googletest/googletest/include)


find_package(HDF5 REQUIRED COMPONENTS C CXX)
include_directories(${HDF5_INCLUDE_DIRS})
find_package(ZLIB REQUIRED COMPONENTS C CXX)
include_directories(${ZLIB_INCLUDE_DIRS})
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})

add_compile_options("-g")
add_compile_options("-DTRACING_ON")
add_compile_options("-I/usr/include/libpng16")
add_compile_options("-llibpng16")
add_compile_options("-I/usr/include/python3.6")
add_compile_options("-lpython3.6")




set(SRC_LIBFDT)
file(GLOB_RECURSE SRC_LIBFDT ext/libfdt/*.c)
add_library(libfdt ${SRC_LIBFDT})

set(SRC_IOSTREAM3)
file(GLOB_RECURSE SRC_IOSTREAM3 ext/iostream3/zfstream.cc)
add_library(iostream3 ${SRC_IOSTREAM3})

set(SRC_NOMALI)
file(GLOB_RECURSE SRC_NOMALI ext/nomali/*.cc)
add_library(nomali ${SRC_NOMALI})

set(SRC_DECODER)
file(GLOB_RECURSE SRC_DECODER ./arch/*.cc ./base/*.cc ./config/*.cc ./cpu/*.cc ./dev/*.cc ./kern/*.cc ./mem/*.cc ./params/*.cc ./sim/*.cc ./enums/*.cc ./python/*.cc)
add_library(decoder ${SRC_DECODER})

add_executable( main main.cc )

target_link_libraries(main PUBLIC decoder ${HDF5_LIBRARIES} ${ZLIB_LIBRARIES} ${PNG_LIBRARY} pthread libfdt iostream3 nomali elf pybind11::module pybind11::embed rt ) # work for zlib