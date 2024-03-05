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
add_executable(cub3D ${MyCSources})




# Call the Makefile in the libft directory
add_custom_target(libft_make ALL
    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libft
)


add_custom_target(mlx ALL
    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mlx_linux
)

# Make sure your executable depends on the libft make target
add_dependencies(cub3D libft_make mlx)






#add libft.a
target_link_libraries(cub3D PRIVATE ${CMAKE_SOURCE_DIR}/libft/libft.a ${CMAKE_SOURCE_DIR}/mlx_linux/libmlx_Linux.a)



# Add extra targets
add_custom_target(re
	COMMAND make clean
	COMMAND make fclean
	COMMAND  make
	VERBATIM
)



add_custom_target(fclean
	COMMAND ${CMAKE_COMMAND} -E echo "Cleaning..."
	COMMAND make clean
	COMMAND ${CMAKE_MAKE_PROGRAM} clean
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libft
	VERBATIM
	)
