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

    //Initialize everything with false
    for(i = 0; i < size; i++)
    {
        vec_states->final = false;
        vec_states->go_back = false;
    }

    return vec_states;
}


void populate_states_vector(state *vec_states)
{
    //Times Sybol
    vec_states[1].final = true;
    vec_states[1].s_token.name = strdup("*");
    vec_states[1].s_token.type = strdup("op_multi");

    //Plus Symbol
    vec_states[2].final = false;   
    vec_states[2].s_token.name = strdup("+");
    vec_states[2].s_token.type = strdup("op_plus");

    //Minus Symbol
    vec_states[3].final = false;
    vec_states[3].s_token.name = strdup("-");
    vec_states[3].s_token.type = strdup("op_minus");
    
    //Division Symbol
    vec_states[4].final = true;
    vec_states[4].s_token.name = strdup("/");
    vec_states[4].s_token.type = strdup("op_div");

    //Interger Number
    vec_states[6].final = true;  
    vec_states[6].go_back = true;   
    vec_states[6].s_token.name = strdup("INTEGER NUMBER");
    vec_states[6].s_token.type = strdup("num_int");

    //Real Number  
    vec_states[9].final = true;  
    vec_states[9].go_back = true;   
    vec_states[9].s_token.name = strdup("REAL NUMBER");
    vec_states[9].s_token.type = strdup("num_real");

    //Identifier
    vec_states[11].final = true;
    vec_states[11].go_back = true;   
    vec_states[11].s_token.name = strdup("ID");
    vec_states[11].s_token.type = strdup("identifier");

    //Open paretheses
    vec_states[12].final = true;
    vec_states[12].s_token.name = strdup("(");
    vec_states[12].s_token.type = strdup("open_parentheses");

    //Comment
    vec_states[14].final = true;
    vec_states[14].s_token.type = strdup("comment");

    //Close parenthese
    vec_states[15].final = true;
    vec_states[15].s_token.name = strdup(")");
    vec_states[15].s_token.type = strdup("close_parentheses");

    //Semicolon Symbol
    vec_states[16].final = true;
    vec_states[16].s_token.name = strdup(";");
    vec_states[16].s_token.type = strdup("simb_semi_colon");

    //Colon Symbol
    vec_states[18].final = true;
    vec_states[18].go_back = true; 
    vec_states[18].s_token.name = strdup(":");
    vec_states[18].s_token.type = strdup("simb_colon");

    //Atribuition Symbol
    vec_states[19].final = true;
    vec_states[19].s_token.name = strdup(":=");
    vec_states[19].s_token.type = strdup("simb_atribution");
   
    //Comma Symbol
    vec_states[20].final = true;
    vec_states[20].s_token.name = strdup(",");
    vec_states[20].s_token.type = strdup("simb_comma");

    //Dot Symbol
    vec_states[21].final = true;
    vec_states[21].s_token.name = strdup(".");
    vec_states[21].s_token.type = strdup("simb_dot");

    //Operator Greater
    vec_states[23].final = true;
    vec_states[23].go_back = true;
    vec_states[23].s_token.name = strdup(">");
    vec_states[23].s_token.type = strdup("op_greater");

    //Operator Greater Than Or Equal
    vec_states[24].final = true;
    vec_states[24].s_token.name = strdup(">=");
    vec_states[24].s_token.type = strdup("op_greater_equal");
    
    //Operator Less
    vec_states[26].final = true;
    vec_states[26].go_back = true;
    vec_states[26].s_token.name = strdup("<");
    vec_states[26].s_token.type = strdup("op_less");
  
    //Operator Less Than Or Equal
    vec_states[27].final = true;
    vec_states[27].s_token.name = strdup("<=");
    vec_states[27].s_token.type = strdup("op_lessr_equal");

    //Operator Not Equal
    vec_states[28].final = true;
    vec_states[28].s_token.name = strdup("<>");
    vec_states[28].s_token.type = strdup("op_not_equal");

}


void free_states_vector(state *vec_states)
{
    free(vec_states);
}
