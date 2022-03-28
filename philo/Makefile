NAME	=	philo

SRC		=	src/philo.c \
			src/init.c \
			src/routines.c \
			src/life_philo.c \
			utils/utils.c \
			utils/utils_1.c 

OBJS	= 	$(SRC:.c=.o)

FLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(FLAGS) -o $(NAME) $(OBJS)

.c.o:
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: re all fclean clean