#FORMATTING

GREEN = "\\033[32m"
BOLD = "\\033[1m"
RESET_FORMAT = "\\033[0m"
ERASE_LINE = "\\033[A\\033[K\\033[A"

#COMPILATION

NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = minilibx-linux/
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

SRC_DIR = ./src/
SRC_FILES = main.c images.c parsing.c player_init.c player_movements.c raycaster_drawing.c raycaster_prep.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIB_DIR = ./libft/
LIB_INC = ./libft/inc/
LIB_FLAGS = -L $(LIB_DIR) -lft
LIB = $(LIB_DIR)libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@echo "Object files related to fdf created"
	@$(CC) $(OBJ) $(MLX_FLAGS) $(LIB_FLAGS) -o $(NAME)
	@echo "$(BOLD)$(NAME)$(RESET_FORMAT) [$(GREEN)OK$(RESET_FORMAT)]"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HDR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(HDR_DIR) -I$(LIB_INC) -I$(MLX_DIR) -c $< -o $@
	@echo "Compiled: $*.o [$(GREEN)OK$(RESET_FORMAT)]"
	@echo "$(ERASE_LINE)"

$(LIB): FORCE
	@make -C $(LIB_DIR)

clean:
	@make -C $(LIB_DIR) clean
	@rm -rf $(OBJ) $(OBJ_DIR)
	@echo "Object files related to fdf deleted"

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -rf $(NAME)
	@echo "$(NAME) deleted"

re:
	@$(MAKE) fclean
	@echo ""
	@$(MAKE) all

FORCE:

.PHONY: all clean fclean re FORCE
