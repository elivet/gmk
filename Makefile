#DEV, BUID
MODE			=	BUILD
ENVIRONEMENT	=	MAC


ifeq ($(MODE), DEV)
	CPPFLAGS	=	-Wall -Wextra -ansi -O3 -DDEBUG
else
	CPPFLAGS	=	-Wall -Wextra -Werror -ansi -O3
endif

ifeq ($(ENVIRONEMENT), MAC)
	INC				=	-I ~/.brew/include/
	LIB				=	-L ~/.brew/lib/ -lglfw3 -framework OpenGL
else
	INC				=	`pkg-config --cflags gl glfw3 x11 xxf86vm xrandr xi xcursor xinerama`
	LIB				=	`pkg-config --libs gl glfw3 x11 xxf86vm xrandr xi xcursor xinerama` -lpthread
endif

CC				=	g++

NAME			=	gomoku

FILES			=	\
					engine/OpenGlLib.cpp\
					engine/CoreEngine.cpp\
					core/GameObject.cpp\
					\
					main.cpp \
					game/Board.cpp \
					game/Pawn.cpp \
					game/Gomoku.cpp \
					game/Player.cpp \
					game/Computer.cpp \
					game/Possibility.cpp \
					game/Alignement.cpp \
					\


SRCS			=	$(FILES)

OBJS			=	$(SRCS:.cpp=.o)

HEADS			=	$(SRCS:.cpp=.hpp)


all:			$(NAME)

$(NAME):		$(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(LIB)
	@printf "\033[33mCompilation of %-40s \033[34m[\033[32m✔\033[34m]\033[0m\n" $(NAME)

$(OBJS):		$(HEADS)

%.o:			%.cpp
	@printf "\t\033[36m-> %-45s\033[34m[\033[32m✔\033[34m]\033[0m\n" $<
	@$(CC) $(CPPFLAGS) -fpic -o $@ -c $< $(INC)

clean:
	@printf "\033[31mRemove %s objects\033[0m\n" $(NAME)
	@rm -rf $(OBJS)

fclean:			clean
	@printf "\033[31mRemove binary\033[0m\n"
	@rm -rf $(NAME)

re:				fclean all

install:
	@if [ ! -d "~/.brew" ] ; \
	then \
		/usr/local/bin/brew update; \
	fi;
	@export HOMEBREW_TEMP=/tmp/mytemp
	@export HOMEBREW_CACHE=/tmp/mycache
	@mkdir -p /tmp/mycache /tmp/mytemp
	@~/.brew/bin/brew install homebrew/versions/glfw3

.PHONY:		all re fclean clean
