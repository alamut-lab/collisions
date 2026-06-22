NAME = collisions

CC = cc
CFLAGS = -Wall -Wextra -Werror # -O3 -g -fno-omit-frame-pointer

ifeq ($(BENCHMARK),1)
	CFLAGS += -D BENCHMARK=true
endif

RM = rm -rf

SRCS_DIR = srcs
OBJ_DIR = objects
DEP_DIR = deps
INCLUDES_DIR = includes

C_FILES		= main.c init_data.c init_particules.c data_tools.c collisions.c build_rt_data.c arena.c apply_bounds.c print.c utils.c

O_FILES		= $(C_FILES:.c=.o)
D_FILES		= $(C_FILES:.c=.d)

SRCS		= $(addprefix $(SRCS_DIR)/, $(C_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(O_FILES))
DEPS		= $(addprefix $(DEP_DIR)/, $(D_FILES))

INCLUDES = -I$(INCLUDES_DIR)


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

all: $(NAME)

$(NAME): $(OBJS)
	$(call BANNER)
	@printf "  $(BYELLOW)⚡ Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)
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
	@mkdir -p $(DEP_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@
	@printf "  $(DIM)$(CYAN)⟩$(RESET) $(DIM)compiled$(RESET) $(CYAN)$<$(RESET)\n"

clean:
	@printf "\n  $(BYELLOW)◌  Sweeping object files...$(RESET)\n"
	@$(RM) $(OBJS) $(DEPS)
	@printf "  $(BGREEN)◌  Objects cleaned$(RESET)\n\n"

fclean: clean
	@printf "  $(RED)◌  Removing binaries...$(RESET)\n"
	@$(RM) $(NAME) $(OBJ_DIR) $(DEP_DIR)
	@printf "  $(BGREEN)◌  Everything wiped$(RESET)\n\n"

-include $(DEPS)

re: fclean all

bench:
	@$(MAKE) re BENCHMARK=1

.PHONY: all clean fclean re bench
