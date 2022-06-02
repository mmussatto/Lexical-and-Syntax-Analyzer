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

 // Creating a vector of states
state* create_state_vector(int ROWS)
{
    int i;
    state* final_states = (state*) calloc(ROWS, sizeof(state));

    for(i = 0; i < ROWS; i++)
    {
        final_states->final = false;
    }

    return final_states;
}


void add_states(state *final_states)
{

    /* ---------- +, -, *, / ----------------*/ 
    final_states[1].final = true;
    final_states[1].s_token.name = "+";
    final_states[1].s_token.type = "simb_mais";

    final_states[2].final = true;   
    final_states[2].s_token.name = "-";
    final_states[2].s_token.type = "simb_menos";


    final_states[3].final = true;
    final_states[3].s_token.name = "*";
    final_states[3].s_token.type = "simb_vezes";
    

    final_states[4].final = true;
    final_states[4].s_token.name = "/";
    final_states[4].s_token.type = "simb_div";

    /* ---------- >, <, >=, <=, <> ----------------*/ 

    final_states[6].final = true;   
    final_states[6].s_token.name = ">";
    final_states[6].s_token.type = "op_maior";

    final_states[7].final = true;   
    final_states[7].s_token.name = ">=";
    final_states[7].s_token.type = "op_maior_igual";

    final_states[9].final = true;   
    final_states[9].s_token.name = "<";
    final_states[9].s_token.type = "op_menor";

    final_states[10].final = true;   
    final_states[10].s_token.name = "<=";
    final_states[10].s_token.type = "op_menor_igual";

    final_states[11].final = true;   
    final_states[11].s_token.name = "<>";
    final_states[11].s_token.type = "op_diferente";


    //State of user identifiers
    final_states[13].final = true;
    final_states[13].s_token.name = NULL;
    final_states[13].s_token.type = "identificador";

    //State of integer numbers
    final_states[16].final = true;
    final_states[16].s_token.name = NULL;
    final_states[16].s_token.type = "numero_inteiro";
    
    //State of real numbers
    final_states[19].final = true;
    final_states[19].s_token.name = NULL;
    final_states[19].s_token.type = "numero_real";

    //State of the end of comments
    final_states[21].final = true;
    final_states[21].s_token.name = NULL;
    final_states[21].s_token.type = "comentario"; //It is not relevant
    
  /*  //State of unvalid character
    final_states[21].final = true;
    final_states[21].s_token.name = ;
    final_states[21].s_token.type = NULL; //It is not relevant
  */
    
}

void free_vector_states(state *final_states)
{
    free(final_states);
}
