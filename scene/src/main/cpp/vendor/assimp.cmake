add_library(assimp INTERFACE)

target_include_directories(assimp SYSTEM INTERFACE
        ${CMAKE_SOURCE_DIR}/vendor/assimp/include
#    ${CMAKE_SOURCE_DIR}/vendor/assimp
#    ${CMAKE_SOURCE_DIR}/vendor/assimp/Compiler
)
