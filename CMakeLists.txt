# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProject)

# Add source fileFILE(GLOB_RECURSE MyCSources ./*.c)
FILE(GLOB_RECURSE MyCSources src/*.c)




# Add linker flags globally
add_link_options(-lm  -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lz )



# Add compiler flags globally
add_compile_options(-Wall -Wextra -Werror -g -O0)



# Add an executable target
add_executable(my_app ${MyCSources} libft.a)



#add libft.a
target_link_libraries(my_app PRIVATE ${CMAKE_SOURCE_DIR}/libft/libft.a ${CMAKE_SOURCE_DIR}/mlx_linux/libmlx_Linux.a)



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
