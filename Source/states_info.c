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
    }

    return vec_states;
}


void populate_states_vector(state *vec_states)
{

    /* ---------- +, -, *, / ----------------*/ 
    vec_states[1].final = true;
    vec_states[1].s_token.name = "+";
    vec_states[1].s_token.type = "simb_mais";

    vec_states[2].final = true;   
    vec_states[2].s_token.name = "-";
    vec_states[2].s_token.type = "simb_menos";


    vec_states[3].final = true;
    vec_states[3].s_token.name = "*";
    vec_states[3].s_token.type = "simb_vezes";
    

    vec_states[4].final = true;
    vec_states[4].s_token.name = "/";
    vec_states[4].s_token.type = "simb_div";

    /* ---------- >, <, >=, <=, <> ----------------*/ 

    vec_states[6].final = true;   
    vec_states[6].s_token.name = ">";
    vec_states[6].s_token.type = "op_maior";

    vec_states[7].final = true;   
    vec_states[7].s_token.name = ">=";
    vec_states[7].s_token.type = "op_maior_igual";

    vec_states[9].final = true;   
    vec_states[9].s_token.name = "<";
    vec_states[9].s_token.type = "op_menor";

    vec_states[10].final = true;   
    vec_states[10].s_token.name = "<=";
    vec_states[10].s_token.type = "op_menor_igual";

    vec_states[11].final = true;   
    vec_states[11].s_token.name = "<>";
    vec_states[11].s_token.type = "op_diferente";


    //State of user identifiers
    vec_states[13].final = true;
    vec_states[13].s_token.name = NULL;
    vec_states[13].s_token.type = "identificador";

    //State of integer numbers
    vec_states[16].final = true;
    vec_states[16].s_token.name = NULL;
    vec_states[16].s_token.type = "numero_inteiro";
    
    //State of real numbers
    vec_states[19].final = true;
    vec_states[19].s_token.name = NULL;
    vec_states[19].s_token.type = "numero_real";

    //State of the end of comments
    vec_states[21].final = true;
    vec_states[21].s_token.name = NULL;
    vec_states[21].s_token.type = "comentario"; //It is not relevant
    
  /*  //State of unvalid character
    vec_states[21].final = true;
    vec_states[21].s_token.name = ;
    vec_states[21].s_token.type = NULL; //It is not relevant
  */
    
}

void free_states_vector(state *vec_states)
{
    free(vec_states);
}
