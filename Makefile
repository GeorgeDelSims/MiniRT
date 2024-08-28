NAME = miniRT

MLX_DIR = ./mlx_linux
MLX = $(MLX_DIR)/libmlx.a

# Compiler tools LINUX
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/mlx-linux -Imlx-linux -g 
LDFLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -g 

# Compiler tools MAC 
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -Imlx-linux -g -DGL_SILENCE_DEPRECATION 
# LDFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -fsanitize=address -g -framework Cocoa #-L/opt/X11/lib -lXext -lX11 -lm

# Source File names:
MAIN = main
PARSING = open_file_rt get_next_line get_next_line_utils parsing_rt parsing_sphere parsing_utils parsing_plane parsing_light parsing_camera parsing_ambient parsing_misconfig parsing_checkdata parsing_checkdatav2 parsing_checkdatav3 parsing_cylinder parsing_checkambient parsing_checkcamera parsing_checklight parsing_checksphere parsing_checkplane parsing_checkcylinder parsing_utilsv2 parsing_checkdatav4 parsing_checkdatav5
UTILS = matrix tuple_arithmetic tuple_arithmetic2 tuple_arithmetic3 cofactors determinants matrix_create matrix_ops matrix_tuple_ops submatrix invert mlx_utils
TRANS = translate_scale rotation objects_init ray_transformation object_transformation
ERROR = error_parsing
LIBFT = ft_strncmp ft_memmove ft_atof ft_atoi
WINDOW = init_window ray_tracing camera
SHADING = light normal reflection material color color2 intersection_functions intersect_cyl intersect_cyl_caps shadows intersect_sphere_plane phong
MLX_FUNCTION = mlx_esc

# Source directory
SRCS_DIR = srcs

# Source Subdirectories:
PARS_DIR = parsing
UTILS_DIR = utils
TRANS_DIR = transformations
ERROR_DIR = error
LIBFT_DIR = libft
WINDOW_DIR = window
SHADING_DIR = shading
MLX_FUNCTION_DIR = mlx_function

# Source Files
SRCS = $(addprefix $(SRCS_DIR)/$(UTILS_DIR)/, $(addsuffix .c, $(UTILS)))\
	$(addprefix $(SRCS_DIR)/$(PARS_DIR)/, $(addsuffix .c, $(PARSING)))\
	$(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(MAIN)))\
	$(addprefix $(SRCS_DIR)/$(TRANS_DIR)/, $(addsuffix .c, $(TRANS)))\
	$(addprefix $(SRCS_DIR)/$(ERROR_DIR)/, $(addsuffix .c, $(ERROR)))\
	$(addprefix $(SRCS_DIR)/$(LIBFT_DIR)/, $(addsuffix .c, $(LIBFT)))\
	$(addprefix $(SRCS_DIR)/$(SHADING_DIR)/, $(addsuffix .c, $(SHADING)))\
	$(addprefix $(SRCS_DIR)/$(WINDOW_DIR)/, $(addsuffix .c, $(WINDOW))) \
	$(addprefix $(SRCS_DIR)/$(MLX_FUNCTION_DIR)/, $(addsuffix .c, $(MLX_FUNCTION)))

# Convert source file names to object file names in the OBJ_DIRS directory
OBJ_DIR = obj
OBJ_DIRS = $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(PARS_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(UTILS_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(TRANS_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(ERROR_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(LIBFT_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(WINDOW_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(SHADING_DIR)) \
	$(addprefix $(OBJ_DIR)/, $(MLX_FUNCTION_DIR))

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o) 

# Rule to build the executable: depends on object directory, object files, and the LIBFT library
# Compiles the object files and LIBFT library into the executable, linking with readline library
all: $(NAME)

$(MLX):
	make all -C $(MLX_DIR)

$(NAME): $(OBJ_DIRS) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIRS): 
	mkdir -p $@

# compilation rule 
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	rm -rf $(OBJ_DIR)/*
	
fclean: clean
	rm -rf $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re
