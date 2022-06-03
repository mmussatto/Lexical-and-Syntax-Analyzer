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
    int i;
    state* vec_states = (state*) calloc(size, sizeof(state));

    for(i = 0; i < size; i++)
    {
        vec_states->final = false;
        vec_states->go_back = false;
    }

    return vec_states;
}


void populate_states_vector(state *vec_states)
{

    // Times Sybol
    vec_states[1].final = true;
    vec_states[1].s_token.name = "*";
    vec_states[1].s_token.type = "times_simb";

    // Plus Symbol
    vec_states[2].final = false;   
    vec_states[2].s_token.name = "+";
    vec_states[2].s_token.type = "plus_simb";

    //Minus Symbol
    vec_states[3].final = false;
    vec_states[3].s_token.name = "-";
    vec_states[3].s_token.type = "minus_simb";
    
    //Division Symbol
    vec_states[4].final = true;
    vec_states[4].s_token.name = "/";
    vec_states[4].s_token.type = "div_simb";

    
    //Interger Number
    vec_states[6].final = true;  
    vec_states[6].go_back = true;   
    vec_states[6].s_token.name = "INTEGER NUMBER";
    vec_states[6].s_token.type = "num_int";


    // Real Number  
    vec_states[9].final = true;  
    vec_states[9].go_back = true;   
    vec_states[9].s_token.name = "REAL NUMBER";
    vec_states[9].s_token.type = "num_real";


    //Identifier
    vec_states[11].final = true;
    vec_states[11].go_back = true;   
    vec_states[11].s_token.name = "ID";
    vec_states[11].s_token.type = "identifier";


    //Comment
    vec_states[13].final = true;
    vec_states[13].s_token.type = "comment";


    //Semicolon Symbol
    vec_states[14].final = true;
    vec_states[14].s_token.name = ";";
    vec_states[14].s_token.type = "semicolon_simb";
    

    //Atribuition Symbol
    vec_states[16].final = true;
    vec_states[16].s_token.name = ":=";
    vec_states[16].s_token.type = "atribution_sim";

   
    //Colon Symbol
    vec_states[17].final = true;
    vec_states[17].go_back = true; 
    vec_states[17].s_token.name = ":";
    vec_states[17].s_token.type = "colon_simb"; 
  
}


void free_states_vector(state *vec_states)
{
    free(vec_states);
}
