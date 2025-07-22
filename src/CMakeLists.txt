find_package(Stb REQUIRED)

add_library(${PROJECT_NAME} 
	SHARED 
		"image/pch.cpp"
		"image/pch.h"
		"image/bitmap.cpp"
)

target_include_directories(${PROJECT_NAME}  
	PUBLIC 
		${PROJECT_SOURCE_DIR}/include
	PRIVATE 
		${Stb_INCLUDE_DIR}
)

target_compile_options(${PROJECT_NAME}
	PRIVATE 
		$<$<CXX_COMPILER_ID:MSVC>:/W4>
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
		"image/pch.h"
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		RETRO_IMAGE_EXPORTS
)