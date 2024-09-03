add_library(opencv2 INTERFACE)

target_include_directories(opencv2 SYSTEM INTERFACE
        ${CMAKE_SOURCE_DIR}/vendor/opencv2/include
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/calib3d
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/core
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/dnn
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/features2d
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/gapi
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/highgui
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/imgcodecs
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/imgproc
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/ml
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/objdetect
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/photo
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/stitching
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/video
#        ${CMAKE_SOURCE_DIR}/vendor/opencv2/videoio
)
