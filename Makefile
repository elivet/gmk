NAME = npuzzle

FLAGS = -Wall -Wextra -Werror

OBJ = main.o Gomoku.o

all: $(NAME)

$(NAME): $(OBJ)
	    g++ $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	    g++ $(FLAGS) -c $<

clean:
	    rm -rf $(OBJ)

fclean: clean
	    rm -rf $(NAME)

re: fclean all