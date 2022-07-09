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

void get_token_from_vector(vec_token* vec_tokens, token *curr_token)
{   
    vec_tokens->n_curr_token++;

    if(curr_token->name != NULL && curr_token->type != NULL)
    {
        free(curr_token->name);
        free(curr_token->type);
    }
    
    curr_token->name = strdup(vec_tokens->tokens[vec_tokens->n_curr_token].name);
    curr_token->type = strdup(vec_tokens->tokens[vec_tokens->n_curr_token].type);
    curr_token->line = vec_tokens->tokens[vec_tokens->n_curr_token].line;

}

int ASD(vec_token* vec_tokens)
{
    token *curr_token = malloc(1*sizeof(token));
    curr_token->name = NULL;
    curr_token->type = NULL;

    get_token_from_vector(vec_tokens, curr_token);

    sytx_programa(vec_tokens, curr_token);

    if (strcmp(curr_token->name, "EOF") == 0)
    {
        free(curr_token->name);
        free(curr_token->type);
        free(curr_token);
        return 1;
    }
    else
    {
        free(curr_token->name);
        free(curr_token->type);
        free(curr_token);
        return 0;
    }
    

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

void sytx_corpo(vec_token* vec_tokens, token *curr_token)
{
    sytx_dc(vec_tokens, curr_token);

    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    //sytx_comandos(vec_tokens, curr_token);    //nao implementado

    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim



}

sytx_dc(vec_token* vec_tokens, token *curr_token)
{
    //sytx_dc_c(vec_tokens, curr_token);

    //sytx_dc_v(vec_tokens, curr_token);

    //sytx_dc_p(vec_tokens, curr_token);
}