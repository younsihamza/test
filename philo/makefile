CC = cc
NAME = philo
flag = -Wall -Werror -Wextra
headr = philo.h
files = check_d_e.c ft_atoi.c philo_help.c philo.c

OBJECT = $(files:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECT)
	$(CC) $^ -o $@

%.o :%.c $(headr)
	$(CC) $(flag) -c $< 

clean :
	rm -f $(OBJECT)

fclean : clean
	rm -f $(NAME)

re : fclean all
