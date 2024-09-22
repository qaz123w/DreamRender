project(interface)

set(INTERFACE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/console.h
    ${CMAKE_CURRENT_SOURCE_DIR}/console.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/interface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/interface.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ROOT_INCLUDE_DIRS}
    ${GLAD_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIRS}
    ${FMT_INCLUDE_DIRS}
)

add_library(interface ${INTERFACE_SRCS})

target_link_libraries(${PROJECT_NAME}
    glad
    glfw
    spdlog
    imgui
    fmt
)