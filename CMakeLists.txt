# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProject)

# Add source files
FILE(GLOB MyCSources ./*.c)

# Add flags to source files
#set_source_files_properties(src/func/test.c PROPERTIES COMPILE_OPTIONS "-Wall;-Werror;-Wextra;-g")

add_compile_options(-Wall -Wextra -Werror -g -O0)
SET(GCC_COVERAGE_COMPILE_FLAGS "-lm")
# Add an executable target
add_executable(my_app ${MyCSources})


# Add extra targets
add_custom_target(re
	COMMAND make clean
	COMMAND  make
	VERBATIM
)

add_custom_target(fclean
	COMMAND ${CMAKE_COMMAND} -E echo "Cleaning..."
	COMMAND make clean
	VERBATIM
	)
