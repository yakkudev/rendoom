cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Set project name and version
project(rendoom VERSION 0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set 64-bit build
set(CMAKE_GENERATOR_PLATFORM x64)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug 
    CACHE STRING 
      "Choose the type of build (Debug or Release)" FORCE)
endif()

# Export compile commands for completion engines (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set option to control setting the resource path variable
option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)

if(NOT USE_INSTALL_RESOURCE_PATH)
  set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/resource/")
else()
  set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/resource/")
endif()

# Generate config.h
configure_file(include/config.h.in config.h)

# Find SFML shared libraries
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Compile executable
add_executable(rendoom src/main.cpp src/color.cpp)

# Set include directory search paths
target_include_directories(rendoom 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

# Set executable RPATH
set_target_properties(rendoom
  PROPERTIES
      INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
  )

# Link executable to required SFML modules
target_link_libraries(rendoom sfml-graphics sfml-audio)

# Set executable install location
install(TARGETS rendoom DESTINATION bin)

# Set install location for resources
install(DIRECTORY resource
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
)

