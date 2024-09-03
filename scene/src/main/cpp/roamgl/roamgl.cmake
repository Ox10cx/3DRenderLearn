add_library(roamgl STATIC
        ${CMAKE_SOURCE_DIR}/roamgl/utils/event.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/log.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/file_utils.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/geo.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/gl/gl_functions.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/roam/roam.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/roam/roam_impl.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/roam/transform.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/roam/transform_state.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/roam/roam_options.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/geometry/gl_geometry.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/shader/shader.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/renderer/renderer.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/texture/texture.cpp
)


target_include_directories(roamgl SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/roamgl
        ${CMAKE_SOURCE_DIR}/roam
        ${CMAKE_SOURCE_DIR}/roamgl/utils
        ${CMAKE_SOURCE_DIR}/roamgl/gl
        ${CMAKE_SOURCE_DIR}/roamgl/geometry
        ${CMAKE_SOURCE_DIR}/roamgl/shader
        ${CMAKE_SOURCE_DIR}/roamgl/renderer
        ${CMAKE_SOURCE_DIR}/roamgl/texture
)

