NAME = socket

DIR_SRC = src
DIR_BIN = out

SRC = main.cpp
BIN = ${SRC:.cpp=.o}

${NAME}: ${BIN}


all: ${NAME}

.PHONY: all re clean fclean