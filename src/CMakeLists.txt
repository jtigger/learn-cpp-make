cmake_minimum_required(VERSION 3.22.0)
project(hello)
add_executable(${PROJECT_NAME} main.cpp)

# Update git submodules (so you don't have to)
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  option(GIT_SUBMODULE_UPDATE "Update git submodules during build" ON)
  if(GIT_SUBMODULE_UPDATE)
    message(STATUS "🚜 Updating git submodule")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recusrive
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                 RESULT VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
      message(FATAL_ERROR "💣 failed (exit status = ${GIT_SUBMOD_RESULT}).")
    endif()
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
  message(FATAL_ERROR "🚨 requires GLFW, but unable to find ${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt; Is GIT_SUBMODULE_UPDATE on?")
endif()


add_subdirectory(adder)
add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME}
  PUBLIC adder 
  PUBLIC external/glfw/include
)

target_link_libraries(${PROJECT_NAME} adder glfw)

