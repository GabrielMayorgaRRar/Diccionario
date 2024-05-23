CC = gcc

SRC = main.c diccionario.c entidad.c atributo.c

TARGET = a.out

all:
	${CC} ${SRC} -o ${TARGET}
clear:
	rm *.out *.PASEME 