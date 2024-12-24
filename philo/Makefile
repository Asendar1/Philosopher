SRC_FILES = main.c parser.c threads.c utils.c
SRCS_DIR = sources/

SRCS = $(addprefix $(SRCS_DIR), $(SRC_FILES))

OBJS_DIR = objects/
OBJS = $(addprefix $(OBJS_DIR), $(SRC_FILES:.c=.o))

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread -Iincludes

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
