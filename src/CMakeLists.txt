#find_package(Boost REQUIRED COMPONENTS property_tree)
#find_package(Boost REQUIRED COMPONENTS beast)
#find_package(Boost REQUIRED COMPONENTS iostreams)
#find_package(boost_algorithm CONFIG REQUIRED)

add_library(${PROJECT_NAME} 
	SHARED 
		"template/pch.cpp"
		"template/pch.h"
)

target_include_directories(${PROJECT_NAME}  
	PUBLIC 
		${PROJECT_SOURCE_DIR}/include
)

#target_link_libraries(${PROJECT_NAME}  
#	PRIVATE 
#		Boost::property_tree
#		Boost::beast
#		Boost::iostreams
#		Boost::algorithm
#)

target_compile_options(${PROJECT_NAME}
	PRIVATE 
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
		$<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -Wconversion -Wshadow>
)

target_compile_options(${PROJECT_NAME}
	PRIVATE 
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:MSVC>>:/Zi /Od>
		$<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU>>:-g>
)

target_compile_options(${PROJECT_NAME}
	PRIVATE 
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/O2>
		$<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-O3>
)

target_precompile_headers(${PROJECT_NAME}
	PRIVATE
		"template/pch.h"
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		RETRO_TEMPLATE_EXPORTS
)