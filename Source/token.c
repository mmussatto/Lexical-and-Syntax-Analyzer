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

#include "Headers/token.h"


vec_token* create_tokens_vector()
{
    vec_token *tk;

    //Allocating the vec_token
    tk = malloc(sizeof(vec_token));
    tk->total_size = 50;        //Totally arbitrary starting value 
    tk->size = 0;

    tk->tokens = malloc(tk->total_size*sizeof(token));
    return tk;
}


token last_vec_token(vec_token* vec_tokens)
{
    token t;

    //Vec_tokens is empty
    if(vec_tokens->size == 0)
    {
        t.name = NULL;
        t.type = NULL;
        return t;
    }
    else
        return vec_tokens->tokens[vec_tokens->size - 1];    //returns the last token in the vector
}


void vec_tokens_push_back(vec_token* vec_tokens, token t)
{

    //Vector too small for new token. Need to reallocate memory
    if(vec_tokens->size == vec_tokens->total_size)
    {
        vec_tokens->total_size *= 2;
        vec_tokens->tokens = realloc(vec_tokens->tokens, vec_tokens->total_size);
    }

    //Push-back new token to vector
    vec_tokens->tokens[vec_tokens->size].name = strdup(t.name);
    vec_tokens->tokens[vec_tokens->size].type = strdup(t.type);
    vec_tokens->size++;
}


void free_tokens_vector(vec_token* vec_tokens)
{
    free(vec_tokens->tokens);
    free(vec_tokens);
}

