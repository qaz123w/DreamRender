cmake_minimum_required(VERSION 3.0.0)

project(dream LANGUAGES C CXX)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add glad
set(GLAD_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog/include)
add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c)

# Add glfw
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_INSTALL OFF)
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

# Add glm
set(GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/glm/include)

# Add spdlog
set(SPDLOG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog)

# Add imgui
set(IMGUI_INCLUDE_DIRS
${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends
)
set(IMGUI_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/misc/cpp/imgui_stdlib.cpp
)
add_library(imgui ${IMGUI_SRCS})

# Add fmt
set(FMT_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/fmt/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/fmt)

# Add nlohmann_json
set(NLOHMANN_JSON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/nlohmann_json/include)

# Add embree
set(EMBREE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/embree/include)
set(EMBREE_LIB_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/embree/lib)

link_directories(
    ${EMBREE_LIB_DIRS}
)

include_directories(
    ${GLAD_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIRS}
    ${FMT_INCLUDE_DIRS}
    ${NLOHMANN_JSON_INCLUDE_DIRS}
    ${EMBREE_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    glad
    glfw
    spdlog
    imgui
    fmt
    embree3
    tbb
)
