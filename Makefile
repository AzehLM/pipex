NAME	:= pipex

include pipex.mk

BUILD_DIR	:= .obj/
OBJS 		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR)%.o,$(SRCS))
OBJSB		:= $(patsubst $(SRCSDIR)%.c,$(BUILD_DIR)%.o,$(SRCSBONUS))	
DEPS		:= $(OBJS:.o=.d)
DEPSB		:= $(OBJSB:.o=.d)

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -MMD -MP -I incs/ -I libft/incs/

RM			:= rm -f
RMDIR		+= -r
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(BUILD_DIR)

.DEFAULT_GOAL	:= all

-include $(DEPS)
-include $(DEPSB)

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

.PHONY: bonus
bonus: .bonus

.bonus: libft/libft.a $(OBJSB)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJSB) -L libft -lft
	@echo "\n$(GREEN_BOLD)✓ $(NAME) is ready$(RESETC)"
	@touch .bonus

$(BUILD_DIR)bonus/%.o: $(SRCSDIR)bonus/%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)[Compiling]$(RESETC) $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@$(MAKE) clean -C libft/
	@$(RM) $(OBJS) $(DEPS) .bonus
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

# ********** valgrind and fsanitize flags ************************************ #

.PHONY: asan
asan: CFLAGS += -fsanitize=address -g
asan: re
	@echo "$(GREEN_BOLD)✓ $(NAME) is compiled with AddressSanitizer$(RESETC)"

.PHONY: valgrind
valgrind: CFLAGS += -g3
valgrind: re
	@echo "$(GREEN_BOLD)✓ $(NAME) is compiled with debug symbols for valgrind$(RESETC)"

.PHONY: asanb
asanb: CFLAGS += -fsanitize=address -g
asanb: bonus
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJSB) -L libft -lft
	@echo "$(GREEN_BOLD)✓ $(NAME) bonus is compiled with AddressSanitizer$(RESETC)"

.PHONY: valgrindb
valgrindb: CFLAGS += -g3
valgrindb: bonus
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJSB) -L libft -lft
	@echo "$(GREEN_BOLD)✓ $(NAME) bonus is compiled with debug symbols for valgrind$(RESETC)"

# ********** COLORS AND BACKGROUND COLORS ************************************ #

RESETC				:=	\033[0m

GREEN_BOLD			:= \033[1;32m
RED_BOLD			:= \033[1;31m
CYAN				:= \033[0;36m
