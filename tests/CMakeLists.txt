find_package(boost_unit_test_framework CONFIG REQUIRED)

add_executable(${PROJECT_NAME}-tests    
    "src/main.cpp" 
    "src/color.test.cpp"
    "src/bitmap.test.cpp"
)

target_link_libraries(${PROJECT_NAME}-tests
    PRIVATE
        ${PROJECT_NAME}
        Boost::unit_test_framework
)

target_compile_definitions(${PROJECT_NAME}-tests
	PRIVATE
		TESTS_RESOURCE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/res"
)

add_test(NAME ${PROJECT_NAME}.Tests COMMAND ${PROJECT_NAME}-tests)