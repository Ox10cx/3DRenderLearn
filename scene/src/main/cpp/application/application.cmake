add_library(app STATIC
        ${CMAKE_SOURCE_DIR}/application/camera/camera.cpp
        ${CMAKE_SOURCE_DIR}/application/camera/orthogonal_camera.cpp
        ${CMAKE_SOURCE_DIR}/application/camera/perspective_camera.cpp
)


target_include_directories(app SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/application/camera
)

