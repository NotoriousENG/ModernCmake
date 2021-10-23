cmake_minimum_required(VERSION 3.15)

# Set the project name
project(ModernCmake VERSION 1.0)

# USE ADDER?
option(USE_ADDER "A simple library for adding two floats" ON)

if (USE_ADDER)
    add_subdirectory(Adder)

    list(APPEND EXTRA_LIB_DIRS Adder)
    list(APPEND EXTRA_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/Adder")
    list(APPEND EXTRA_LINKS adder)
endif()
# END USE ADDER?

configure_file(config.h.in config.h)

# add the executable
add_executable(ModernCmake main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# Download all the submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# Check all the submodules
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
        PUBLIC external/glfw/include
        ${EXTRA_INCLUDE_DIRS}
    )

target_link_directories(${PROJECT_NAME} 
        PRIVATE external/glfw/src
        ${EXTRA_LIB_DIRS}
    )

target_link_libraries(${PROJECT_NAME}
 	glfw
    ${EXTRA_LINKS}
 )


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${ModernCmake_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${ModernCmake_VERSION_MINOR})
include(CPack)