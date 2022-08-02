#
#  ****************************************************
#  *                                                  *
#  * SSC 0605 - Teoria da Computação e Compiladores   *
#  *                                                  *
#  * Autores:                                         *
#  *  - Che Fan Pan                       - 11200421  *
#  *  - Eduardo Cavalari Valença          - 11234381  *
#  *  - Marcos Vinicius Firmino Pietrucci - 10770072  *
#  *  - Murilo Mussatto                   - 11234245  *
#  *                                                  *
#  * São Carlos - SP                                  *
#  * 2022                                             *
#  *                                                  *
#  ****************************************************

CC=gcc					# C compiler

CFLAGS=-I. -g -Wall

DEPS= *.h Headers/*.h	

OBJ = *.c Source/*.c 

FILE = test.txt

all: $(OBJ)
	@$(CC) -o prog $^ $(CFLAGS) $(LIBS)

o: %.c $(DEPS)		
	@$(CC) -c -o $@ $< $(CFLAGS)

run:
	@read -p "Insira o nome do arquivo (com extensao): "  NOME; \
	./prog $${NOME};

clean:
	@rm -f *.o prog error_file.txt output.txt
	
