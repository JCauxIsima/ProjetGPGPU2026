
cmake_minimum_required( VERSION 3.18 )

project( NomCool VERSION 1.0.0 LANGUAGES CUDA CXX )

message( STATUS "**** Configuring ${PROJECT_NAME} version ${PROJECT_VERSION} ****")

# Checking CUDA availability
include(CheckLanguage)
check_language(CUDA)

set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_ARCHITECTURES 50)

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

add_compile_options( -Wall -Werror -Wno-deprecated )

if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:\"LIBCMT\"")
endif()

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
set( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE} )

add_library(base)

target_sources(base
  PRIVATE
    src/cpp_test_compil.cpp
)
target_sources(base
  PRIVATE
    src/cuda_test_compil.cu
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    base
)

add_subdirectory( src_test_original )

