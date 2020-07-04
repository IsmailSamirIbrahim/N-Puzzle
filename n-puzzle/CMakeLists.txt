cmake_minimum_required(VERSION 3.9)

# list the header files
set(HEADER_FILES
	include/n-puzzle/N_Puzzle.h
	include/n-puzzle/Priority_Queue.h
)

# list the source files
set(SOURCE_FILES
	src/n-puzzle/N_Puzzle.cpp
	src/n-puzzle/Priority_Queue.cpp
)

# add library target
add_library(n-puzzle
	${HEADER_FILES}
	${SOURCE_FILES}
)

add_library(IsmailSamirIsmail::n-puzzle ALIAS n-puzzle)


# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

# Windows specfic flags to enable W variations of winapi
if(WIN32)
	target_compile_definitions(n-puzzle
		PRIVATE
			UNICODE=1
			_UNICODE=1
		PUBLIC
			OS_WINDOWS=1
	)
	target_link_libraries(n-puzzle
		PRIVATE
			dbghelp
	)
	target_compile_options(n-puzzle
		PRIVATE
			/WX /W4
	)
elseif(UNIX)
	target_link_libraries(n-puzzle
		PRIVATE
			pthread
	)
	target_compile_definitions(n-puzzle
		PUBLIC
			OS_LINUX=1
	)
	target_compile_options(n-puzzle
		PRIVATE
			-Wall -Werror
	)
endif()


# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(n-puzzle PUBLIC cxx_std_17)
set_target_properties(n-puzzle PROPERTIES
	CXX_EXTENSIONS OFF
	DEBUG_POSTFIX d
)

# define debug macro
target_compile_definitions(n-puzzle PRIVATE "$<$<CONFIG:DEBUG>:DEBUG>")

# generate exports header file
include(GenerateExportHeader)
generate_export_header(n-puzzle
	EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/n-puzzle/Exports.h
)

# list include directories
target_include_directories(n-puzzle
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
)
