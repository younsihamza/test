CC = cc 
FLAGS = -Wall -Wextra -Werror
FILES = ft_atoi.c help_philo.c philo.c
NAME = philo_bonus
HD = philo.h
OBJECT = $(FILES:.c=.o);
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJECT)
	$(CC) $^ -o $@

%.o:%.c $(HD)
	$(CC) $(FLAGS) -c $<

clean :
	$(RM) $(OBJECT)

fclean : clean
	$(RM) $(NAME) 