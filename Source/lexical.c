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

#include "Headers/lexical.h"

bool check_plusminus_state(int curr_state, vec_token *vec_tokens){
    
    if (curr_state == STATE_PLUS || curr_state == STATE_MINUS)
    {
        if(strcmp(last_vec_token(vec_tokens).type, "num_int")== 0)
            return true;

        if(strcmp(last_vec_token(vec_tokens).type, "num_real")== 0)
            return true;

        if(strcmp(last_vec_token(vec_tokens).type, "identifier")== 0)
            return true;
    }

    return false;
}

token get_token(FILE* program, int **transition_matrix, state *vec_states, vec_token* vec_tokens, error* vec_errors)
{

    char character;
    int curr_state = 0;
    int n_characters_read = 0;

    //Loop while there are characters to read or the automaton hasn't reached a final state
    while(read_character(program, &character))
    {
        //Get the transition value
        curr_state = transition_matrix[curr_state][(int)character];

        if(curr_state != 0)
            n_characters_read++;

        printf("%c , %d\n", character, curr_state);

        //Error state
        if (curr_state < 0)
            return create_error_token(program, vec_errors, abs(curr_state), n_characters_read);

        //Testing if we are on a final state
        if(vec_states[curr_state].final || check_plusminus_state(curr_state, vec_tokens))
        {
            //retroceder
            if(vec_states[curr_state].go_back)
            {
                move_back_fp(program, 1);       //remove look ahead token from file pointer
                n_characters_read--;
            }
            
            return create_token(program, vec_states, curr_state, n_characters_read);
        }

    }

    if(n_characters_read == 0)
        return create_EOF_token();
    else{
        curr_state = -5; //EOF while unclosed comment
        return create_error_token(program, vec_errors, abs(curr_state), n_characters_read);
    }
}


token create_token(FILE* fp, state* vec_states, int curr_state, int characters)
{
    token t;
    char *string;
    move_back_fp(fp, characters);
    string = read_file_string(fp, characters);
    //t.name = strdup(string);
    t.name = strndup(string, characters);
    t.type = strdup(vec_states[curr_state].s_token.type);

    return t;
}


token create_error_token(FILE* fp, error* vec_errors, int curr_state, int characters)
{
    token t;
    char *string;
    move_back_fp(fp, characters);
    string = read_file_string(fp, characters);
    //t.name = strdup(string);
     t.name = strndup(string, characters);
    t.type = strdup(vec_errors[curr_state].error_token.type);

    return t;
}


token create_EOF_token()
{
    token t;
    t.name = strdup("EOF");
    t.type = strdup("IT'S OVER ANAKIN! THE PROGRAM WAS TOKENIZED!");
    return t;
}

