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
 
#include "Headers/states_info.h"


state* create_states_vector(int size)
{
    //Controll variables
    int i;

    //Allocate the vector
    state* vec_states = (state*) calloc(size, sizeof(state));

    //Initialize everything with false
    for(i = 0; i < size; i++)
    {
        vec_states->final = false;
        vec_states->go_back = false;
    }

    return vec_states;
}


void free_states_vector(state *vec_states)
{
    free(vec_states);
}


void populate_states_vector(state *vec_states, char* file_name)
{
    FILE *tsv = open_file(file_name, 'r'); 

    read_state_tsv_file(tsv, vec_states);   

    fclose(tsv);

}


void read_state_tsv_file(FILE *tsv, state* vec_states)
{
    //Consider the file already opened

    //Control variables
    int i;
    char s_final[50];
    char s_name[50];
    char s_type[50];
    char s_go_back[50];
    
    //Read information from the tvs file
    while (fscanf(tsv, "%d\t%s\t%s\t%s\t%s", &i, s_final, s_name, s_type, s_go_back) != -1 )
    {
        //Create token
        vec_states[i].s_token.name = strdup(s_name);
        vec_states[i].s_token.type = strdup(s_type);
        
        //State is final
        if(strcmp(s_final, "true") == 0)
            vec_states[i].final = true;

        //Look ahead token has been read
        if(strcmp(s_go_back, "true") ==0)
            vec_states[i].go_back = true;
            
    }
    
}



