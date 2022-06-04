# Marcos Vinícus Firmino Pietrucci 10770072 ^-^
CC=gcc					# C compiler

CFLAGS=-I. -g -Wall

#LIBS=-lm

DEPS= *.h Source/*.h	

OBJ = *.c Source/*.c 

FILE = meu_programa.txt

all: $(OBJ)
	@$(CC) -o prog $^ $(CFLAGS) $(LIBS)

o: %.c $(DEPS)		
	@$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: run
run:
	@./prog $(FILE)

#Os comandos abaixo não são utilizados
.PHONY: clean

clean:
	@rm -f *.o prog saida.txt 
