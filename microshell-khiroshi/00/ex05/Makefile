

SRC = ./main.c

SRC += ./init/dup_env.c
SRC += ./init/init.c

SRC += ./builtin/builtin_cd.c
SRC += ./builtin/builtin_echo.c
SRC += ./builtin/builtin_env.c
SRC += ./builtin/builtin_exit.c
SRC += ./builtin/builtin_export.c
SRC += ./builtin/builtin_pwd.c
SRC += ./builtin/builtin_unset.c

SRC += ./utils/env_lst.c
SRC += ./utils/is_long.c
SRC += ./utils/split.c
SRC += ./utils/substr.c
SRC += ./utils/xmalloc.c

OBJ := $(SRC:.c=.o)

NAME = minishell

$(NAME) : $(OBJ)
	gcc  $(OBJ) -lreadline -o $(NAME)
PHONY: all
all: $(NAME)



%.o: %.c
	$(CC) $(CFLAGS) -c -I./include -o $@ $<

PHONY: clean
clean:
	@echo "$(_RED)Removing object files....$(_END)"
	@rm -f $(OBJ)

PHONY: fclean
fclean:
	@echo "$(_RED)Removing object files and program....$(_END)"
	@rm	-f $(NAME)
	@rm -f $(OBJ)