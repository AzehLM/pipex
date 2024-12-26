NAME		:= libft.a

include libft.mk

BUILD_DIR	:= .build/
OBJS 		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR)%.o,$(SRCS))
DEPS		:= $(OBJS:.o=.d)

# ********** FLAGS AND COMPILATION FLAGS ************************************* #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3
CPPFLAGS	:= -MMD -MP -I . -I incs/

AR			:= ar
ARFLAGS		:= -r -c -s

RM			:= rm -f
RMDIR		+= -r
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(BUILD_DIR)

.DEFAULT_GOAL	:= all

# ********** RULES *********************************************************** #

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "\n$(GREEN_BOLD)✓ $(NAME) is ready$(RESETC)\n"

$(BUILD_DIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)[Compiling]$(RESETC) $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(RMDIR) $(NAME) $(BUILD_DIR)
	@echo "$(RED_BOLD)✓ libft is fully cleaned!$(RESETC)"

re: fclean all

.PHONY: all clean fclean re

.SILENT: clean fclean

# ********** COLORS AND BACKGROUND COLORS ************************************ #

RESETC				:= \033[0m

GREEN_BOLD			:= \033[1;32m
RED_BOLD			:= \033[1;31m
CYAN				:= \033[0;36m
