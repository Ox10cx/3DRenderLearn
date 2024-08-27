add_library(roamgl STATIC
        ${CMAKE_SOURCE_DIR}/roamgl/utils/event.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/log.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/file_utils.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/gl_functions.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/gl_geometry.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/shader/shader.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/renderer/renderer.cpp
)


target_include_directories(roamgl SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/roamgl/utils
        ${CMAKE_SOURCE_DIR}/roamgl/glframework
        ${CMAKE_SOURCE_DIR}/roamgl/shader
        ${CMAKE_SOURCE_DIR}/roamgl/renderer
)

