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
#include "Source/Lexical.h"

int main(int argc, char** argv)
{
    //Minion Gostoso  ^-^
    FILE *program = read_file(argv[1],'r');

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
    int **transition_matrix = create_matrix();
    populate_matrix(transition_matrix);

    state* final_states = create_state_vector();
    populate_vector(final_states);

    token t = get_token(program, transition_matrix, final_states);

    //free data structures
    free_matrix(transition_matrix);
    free_vector(final_states);
    
    fclose(program);
    return 0;
}