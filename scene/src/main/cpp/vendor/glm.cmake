add_library(glm INTERFACE)

target_include_directories(glm SYSTEM INTERFACE
        ${CMAKE_SOURCE_DIR}/vendor/glm/include
#    ${CMAKE_SOURCE_DIR}/vendor/glm/detail
#    ${CMAKE_SOURCE_DIR}/vendor/glm/ext
#    ${CMAKE_SOURCE_DIR}/vendor/glm/gtc
#    ${CMAKE_SOURCE_DIR}/vendor/glm/gtx
#    ${CMAKE_SOURCE_DIR}/vendor/glm/simd
)
