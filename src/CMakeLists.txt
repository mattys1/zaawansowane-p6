file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE LIB_FILES *.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

add_library(${PROJECT_NAME}_lib STATIC ${SRC_FILES} ${LIB_FILES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC .)
