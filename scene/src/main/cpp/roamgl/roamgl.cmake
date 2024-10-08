add_library(roamgl STATIC
        ${CMAKE_SOURCE_DIR}/roamgl/utils/event.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/log.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/file_utils.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/gl_functions.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/gl_geometry.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/shader/shader.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/renderer/renderer.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/texture/texture.cpp
)


target_include_directories(roamgl SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/roamgl/utils
        ${CMAKE_SOURCE_DIR}/roamgl/glframework
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/shader
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/renderer
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/texture
)

