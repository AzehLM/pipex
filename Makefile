NAME	:= pipex

include pipex.mk

BUILD_DIR	:= .obj/
OBJS 		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR)%.o,$(SRCS))
DEPS		:= $(OBJS:.o=.d)

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=address
CPPFLAGS	:= -MMD -MP -I incs/ -I libft/incs/

RM			:= rm -f
RMDIR		+= -r
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(BUILD_DIR)

.DEFAULT_GOAL	:= all

-include $(DEPS)

.PHONY: all
all: $(NAME)

$(NAME): libft/libft.a Makefile $(OBJS) 
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS) -L libft -lft
	@echo "\n$(GREEN_BOLD)✓ $(NAME) is ready$(RESETC)"

libft/libft.a: FORCE
	@$(MAKE) -C libft

$(BUILD_DIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)[Compiling]$(RESETC) $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@$(MAKE) clean -C libft/
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(RED_BOLD)[Cleaning]$(RESETC)"

.PHONY: fclean
fclean: clean
	@$(MAKE) fclean -C libft/
	$(RM) $(RMDIR) $(NAME) $(BUILD_DIR)
	@echo "$(RED_BOLD)✓ push_swap is fully cleaned!$(RESETC)"

.PHONY: re
re: fclean all

.PHONY: FORCE
FORCE:

.SILENT: clean fclean

# ********** COLORS AND BACKGROUND COLORS ************************************ #

RESETC				:=	\033[0m

GREEN_BOLD			:= \033[1;32m
RED_BOLD			:= \033[1;31m
CYAN				:= \033[0;36m

