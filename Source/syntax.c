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

#include "Headers/syntax.h"
token* get_token_from_vector(vec_token* vec_tokens, token *curr_token)
{   
    vec_tokens->n_curr_token++;

    curr_token->name = strdup(vec_tokens->tokens[vec_tokens->n_curr_token].name);
    curr_token->type = strdup(vec_tokens->tokens[vec_tokens->n_curr_token].type);
    curr_token->line = vec_tokens->tokens[vec_tokens->n_curr_token].line;

    //curr_token->name = vec_tokens->tokens[vec_tokens->n_curr_token].name;
    return curr_token;
}
