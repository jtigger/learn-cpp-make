cmake_minimum_required(VERSION 3.22.0)
project(hello VERSION 1.2)
add_executable(${PROJECT_NAME} src/main.cpp)

option(GIT_SUBMODULE_UPDATE "Update git submodules during build" ON)
if(GIT_SUBMODULE_UPDATE)
  message(STATUS "🛠  Updating git submodules")
  find_package(Git)
  if(NOT GIT_FOUND)
    message(FATAL_ERROR "🛑 Unable to locate git; is git installed?")
  endif()
  if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(FATAL_ERROR "🛑 project source dir (i.e. ${PROJECT_SOURCE_DIR}) does not contain a git repo; is that the right directory for the source of this project? did you git clone it or download a ZIP?")
  endif()
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} 
    RESULT_VARIABLE GIT_SUBMODULE_RESULT
  )
  if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
    message(FATAL_ERROR "💣 failed (exit status = ${GIT_SUBMOD_RESULT}).")
  endif()
endif()

option(USE_ADDER "Use custom library for adding two floats" ON)
if(USE_ADDER)
  add_subdirectory(lib/adder)
  target_link_libraries(${PROJECT_NAME} adder)
endif()

add_subdirectory(lib/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glfw/include)
target_link_libraries(${PROJECT_NAME} glfw)

configure_file(include/HelloConfig.h.in include/HelloConfig.h)
target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_BINARY_DIR}/include
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${PROJECT_BINARY_DIR}/include/HelloConfig.h DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set(CPACK_GENERATOR "DragNDrop")
include(CPack)
