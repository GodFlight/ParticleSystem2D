
NAME	:= 		Particle_System

SRC_DIR := 		./src
INC_DIR := 		./include
OBJ_DIR	:=		./obj
LIB_DIR	:=		./libft

CC		:= 		gcc
CFLAGS	:= 		-fsanitize=address

SRC		:=		main.c				            \
				cl_processing.c		            \
				init_cl.c	    	            \
				init_sdl.c		                \
				main_and_event_init.c           \
				particle_init.c	            \

SRCS	:=		$(addprefix $(SRC_DIR)/, $(SRC))
OBJ		:= 		$(SRC:.c=.o)
OBJS	:=		$(addprefix $(OBJ_DIR)/, $(OBJ))

FT		:=		./libft/
FT_LIB	:=		$(addprefix $(FT),libft.a)
FT_INC	:=		-I ./libft/include
SDL_INC :=			-I./frameworks/SDL2.framework/Versions/A/Headers \
					-I./frameworks/SDL2_image.framework/Versions/A/Headers \
					-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
					-I./frameworks/SDL2_mixer.framework/Versions/A/Headers \

FRAMEWORKS :=      -F./frameworks \
					-rpath ./frameworks \
					-framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer

FT_LNK  :=      -L ./libft -l ft

all:			dirs $(FT_LIB) $(OBJ_DIR) $(NAME)

$(FT_LIB):
				make -C $(FT)
dirs:			$(OBJ_DIR) $(JC_DIR)

$(OBJ_DIR):
				mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				$(CC) -c $< $(CFLAGS) -I $(INC_DIR) $(FT_INC) $(SDL_INC) -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(FT_LNK) $(SDL_INC) $(OBJS) $(FRAMEWORKS) -o $(NAME) -framework OpenCL

clean:
				rm -f $(OBJS)
				make -C $(FT) clean

fclean: 		clean
				rm -f $(NAME)
				rm -rf $(OBJ_DIR)
				make -C $(FT) fclean

re: 			fclean all
