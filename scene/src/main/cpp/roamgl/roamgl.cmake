add_library(roamgl STATIC
        ${CMAKE_SOURCE_DIR}/roamgl/glframework/gl_functions.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/event.cpp
        ${CMAKE_SOURCE_DIR}/roamgl/utils/log.cpp
)


target_include_directories(roamgl SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/roamgl/utils
        ${CMAKE_SOURCE_DIR}/roamgl/glframework
)

