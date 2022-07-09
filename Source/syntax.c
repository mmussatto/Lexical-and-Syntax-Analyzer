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

int ASD(vec_token* vec_tokens)
{
    token *curr_token = malloc(1*sizeof(token));

    get_token_from_vector(vec_tokens, curr_token);

    sytx_programa(vec_tokens, curr_token);

    if (strcmp(curr_token->name, "EOF") == 0)
        return 1;
    else
        return 0;
    
    

}

void sytx_programa(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "program") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
    
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    sytx_corpo(vec_tokens, curr_token);
    

    return;
    
}
