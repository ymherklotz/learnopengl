set(EXTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/libs")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${EXTERNAL}/glfw")

add_subdirectory("${EXTERNAL}/glad")

file(GLOB SOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")

add_executable(logl
  "${SOURCES}")

target_include_directories(logl
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${EXTERNAL}/glm")

target_link_libraries(logl glfw glad)
