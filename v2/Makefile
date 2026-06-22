NAME = collisions

CC = cc
CFLAGS = -g -O3 -ffast-math -fopt-info-vec-optimized -march=native -mtune=native -Wall -Wextra -flto -lm -fno-omit-frame-pointer
# -fopt-info-vec-optimized -fopt-info-vec-missed -fno-inline

RM = rm -rf

SRCS_DIR = srcs
OBJ_DIR = objects
INCLUDES_DIR = includes

C_FILES		= 	apply_bounds.c arena.c benchmark.c count_sort.c init_data.c main.c simulation.c utils.c viz.c lut.c collisions.c

O_FILES		= $(C_FILES:.c=.o)

SRCS		= $(addprefix $(SRCS_DIR)/, $(C_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(O_FILES))

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I$(INCLUDES_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #

BLACK		= \033[0;30m
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
WHITE		= \033[0;37m

BRED		= \033[1;31m
BGREEN		= \033[1;32m
BYELLOW		= \033[1;33m
BBLUE		= \033[1;34m
BMAGENTA	= \033[1;35m
BCYAN		= \033[1;36m
BWHITE		= \033[1;37m

DIM			= \033[2m
ITALIC		= \033[3m
BOLD		= \033[1m
UNDERLINE	= \033[4m
BLINK		= \033[5m
RESET		= \033[0m

# **************************************************************************** #
#                                 PROGRESS BAR                                 #
# **************************************************************************** #

TOTAL_SRCS	= $(words $(SRCS))
COMPILED	= 0

define print_progress
	$(eval COMPILED := $(shell echo $$(($(COMPILED)+1))))
	$(eval PCT := $(shell echo $$(($(COMPILED) * 100 / $(TOTAL_SRCS)))))
	$(eval FILLED := $(shell echo $$(($(COMPILED) * 20 / $(TOTAL_SRCS)))))
	$(eval EMPTY := $(shell echo $$((20 - $(FILLED)))))
	@printf "\r  $(CYAN)▕$(BGREEN)$(shell printf '█%.0s' $(shell seq 1 $(FILLED) 2>/dev/null || true))$(DIM)$(shell printf '░%.0s' $(shell seq 1 $(EMPTY) 2>/dev/null || true))$(RESET)$(CYAN)▏$(RESET) $(BYELLOW)$(PCT)%%$(RESET) $(DIM)$<$(RESET)      "
endef

# **************************************************************************** #
#                                  BANNER                                      #
# **************************************************************************** #

define BANNER
	@printf "\n"
	@printf "   $(BCYAN) ██████╗ ██████╗ ██╗     ██╗     ██╗███████╗██╗ ██████╗ ███╗   ██╗███████╗$(RESET)\n"
	@printf "   $(BCYAN)██╔════╝██╔═══██╗██║     ██║     ██║██╔════╝██║██╔═══██╗████╗  ██║██╔════╝$(RESET)\n"
	@printf "   $(BCYAN)██║     ██║   ██║██║     ██║     ██║███████╗██║██║   ██║██╔██╗ ██║███████╗$(RESET)\n"
	@printf "   $(CYAN)██║     ██║   ██║██║     ██║     ██║╚════██║██║██║   ██║██║╚██╗██║╚════██║$(RESET)\n"
	@printf "   $(CYAN)╚██████╗╚██████╔╝███████╗███████╗██║███████║██║╚██████╔╝██║ ╚████║███████║$(RESET)\n"
	@printf "   $(DIM) ╚═════╝ ╚═════╝ ╚══════╝╚══════╝╚═╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝$(RESET)\n"
	@printf "                         $(DIM)$(ITALIC)by rstarcev @ 42$(RESET)\n"
	@printf "\n"
endef

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(MLX) $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(call BANNER)
	@printf "  $(BYELLOW)⚡ Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)
	@printf "\n"
	@printf "  $(BGREEN)╔══════════════════════════════════════════════════════╗$(RESET)\n"
	@printf "  $(BGREEN)║$(RESET)                                                      $(BGREEN)║$(RESET)\n"
	@printf "  $(BGREEN)║$(RESET)   $(BWHITE)✦  $(NAME) compiled!$(RESET)                            $(BGREEN)║$(RESET)\n"
	@printf "  $(BGREEN)║$(RESET)      $(DIM)...                  $(RESET)                           $(BGREEN)║$(RESET)\n"
	@printf "  $(BGREEN)║$(RESET)                                                      $(BGREEN)║$(RESET)\n"
	@printf "  $(BGREEN)╚══════════════════════════════════════════════════════╝$(RESET)\n"
	@printf "\n"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "  $(DIM)$(CYAN)⟩$(RESET) $(DIM)compiled$(RESET) $(CYAN)$<$(RESET)\n"

$(MLX):
	printf "INC=/usr/include\n" > $(MLX_DIR)/Makefile.gen
	grep -v '%%%%' $(MLX_DIR)/Makefile.mk >> $(MLX_DIR)/Makefile.gen
	$(MAKE) -C $(MLX_DIR) -f Makefile.gen CC=gcc CFLAGS="-O3 -std=gnu17 -I/usr/include"

clean:
	@printf "\n  $(BYELLOW)◌  Sweeping object files...$(RESET)\n"
	@$(RM) $(OBJS) 
	@printf "  $(BGREEN)◌  Objects cleaned$(RESET)\n\n" 

fclean: clean
	@printf "  $(RED)◌  Removing binaries...$(RESET)\n"
	@$(RM) $(NAME) $(OBJ_DIR)
	@printf "  $(BGREEN)◌  Everything wiped$(RESET)\n\n"
	$(MAKE) -C $(MLX_DIR) -f Makefile.gen clean || true

re: fclean all


.PHONY: all clean fclean re
