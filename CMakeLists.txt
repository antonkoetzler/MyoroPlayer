cmake_minimum_required(VERSION 3.0)

project(MyoroPlayer)

find_package(wxWidgets REQUIRED core base)
include("${wxWidgets_USE_FILE}")

aux_source_directory(./src/ SRC)
include_directories(./include/)

add_executable(
  ${PROJECT_NAME}
  ${SRC}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${wxWidgets_LIBRARIES}
)
