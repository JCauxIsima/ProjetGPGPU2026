
find_package(X11 COMPONENTS X11)

add_executable(test_original main_code_source_4.cpp)
target_link_libraries(test_original
  PRIVATE
    ${X11_LIBRARIES}
)
target_include_directories(test_original
  PRIVATE
    ${X11_INCLUDE_DIR}
)
