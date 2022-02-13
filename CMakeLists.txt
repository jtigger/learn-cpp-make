cmake_minimum_required(VERSION 3.22.0)
project(hello)
add_executable(${PROJECT_NAME} src/main.cpp)

# Update git submodules (so you don't have to)
find_package(Git)
if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
  message(STATUS "${PROJECT_SOURCE_DIR}/.git found")
else()
  message(STATUS "${PROJECT_SOURCE_DIR}/.git NOT found")
endif()
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  option(GIT_SUBMODULE_UPDATE "Update git submodules during build" ON)
  message(STATUS "GIT_SUBMODULE_UPDATE = ${GIT_SUBMODULE_UPDATE}")
  if(GIT_SUBMODULE_UPDATE)
    message(STATUS "🚜 Updating git submodule")
    execute_process(
      COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive 
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} 
      RESULT_VARIABLE GIT_SUBMODULE_RESULT
    )
    if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
      message(FATAL_ERROR "💣 failed (exit status = ${GIT_SUBMOD_RESULT}).")
    endif()
  endif()
else()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/glfw/CMakeLists.txt")
  message(FATAL_ERROR "🚨 requires GLFW, but unable to find ${PROJECT_SOURCE_DIR}/lib/glfw/CMakeLists.txt; Is GIT_SUBMODULE_UPDATE on?")
endif()


add_subdirectory(lib/adder)
add_subdirectory(lib/glfw)

target_include_directories(${PROJECT_NAME}
  PUBLIC lib/glfw/include
)

target_link_libraries(${PROJECT_NAME} adder glfw)

