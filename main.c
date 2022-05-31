/*
 * **************************************************
 *                                                  *
 * SSC 0605 - Teoria da Computação e Compiladores   *
 *                                                  *
 * Autores:                                         *
 *  - Che Fan Pan                       - 11200421  *
 *  - Eduardo Cavalari Valença          - 11234381  *
 *  - Marcos Vinicius Firmino Pietrucci - 10770072  *
 *  - Murilo Mussatto                   - 11234245  *
 *                                                  *
 * São Carlos - SP                                  *
 * 2022                                             *
 *                                                  *
 * **************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include "Source/file.h"

int main(int argc, char** argv)
{
    //Minion Gostoso  ^-^
    FILE *program = read_file(argv[1],'r');
    char token;

    if(argc != 2)
    {
        printf("Provide just the name of the file\n");
        return 1;
    }
   
    if(program == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    
    /*------ Lexical analyser logic --------*/
    while(read_character(program, &token))
    {
        printf("%c", token);
        //Implementing the finite state
    }
    
    fclose(program);
    return 0;
}