
cmake_minimum_required (VERSION 3.23)

project (q_ary_search_demo)

set(CMAKE_CXX_STANDARD 14)

set (HEADER_FILES
	q_ary_search.hpp 
	)
	
set (SOURCE_FILES
	main.cpp
	)
	
add_executable ( q_ary_search_demo ${HEADER_FILES} ${SOURCE_FILES} )
# target_include_directories( q_ary_search_demo PRIVATE ${ML_DIR} )
