file(GLOB_RECURSE SRC_FILES *.cpp *.h)
set(TESTS_EXECUTABLE ${PROJECT_NAME}_tests)

enable_testing()

add_executable(${TESTS_EXECUTABLE} ${SRC_FILES})

target_link_libraries(
	${TESTS_EXECUTABLE} PUBLIC
	${PROJECT_NAME}_lib
	GTest::gtest_main
)
