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
    tk->total_size = 50;    //Totally arbitrary starting value 
    tk->size = 0;
    tk->n_curr_token = -1;    //function get_token_from_vector increments the counter, so it starts with -1. 

    //Allocating the tokens vector
    tk->tokens = malloc(tk->total_size*sizeof(token));
    return tk;
}


void free_tokens_vector(vec_token* vec_tokens)
{

    int i;
    for(i = 0; i < vec_tokens->size; i++)
    {   
        free(vec_tokens->tokens[i].name);
        free(vec_tokens->tokens[i].type);
    }

    free(vec_tokens->tokens);
    free(vec_tokens);
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
        return vec_tokens->tokens[vec_tokens->size - 1];    //Returns the last token in the vector
}


void vec_tokens_push_back(vec_token* vec_tokens, token* t)
{

    //Vector too small for new token. Need to reallocate memory
    if(vec_tokens->size == vec_tokens->total_size)
    {
        vec_tokens->total_size *= 2;
        vec_tokens->tokens = realloc(vec_tokens->tokens, vec_tokens->total_size);
    }

    if(strcmp(t->type,"comment") != 0)
    {
        //Push-back new token to vector
        vec_tokens->tokens[vec_tokens->size].name = strdup(t->name);
        vec_tokens->tokens[vec_tokens->size].type = strdup(t->type);
        vec_tokens->tokens[vec_tokens->size].line = t->line;
        vec_tokens->size++;
    }

    free(t->name);
    free(t->type);
    free(t);
}


void write_tokens_file(FILE *fp, vec_token *vec_tokens)
{
    //Control variables
    int i;
    char enter = '\n';
    token t;
    char *substring;

    //Traverse the tokens vector
    for(i = 0; i < vec_tokens->size; i++)
    {   
        //Get the current token
        t = vec_tokens->tokens[i];

        if(strlen(vec_tokens->tokens[i].type) > 5)
        {
            substring = strndup(vec_tokens->tokens[i].type, 5);
            if(strcmp(substring, "ERROR") == 0)
                continue;
            free(substring);
        }

        //Write the name of the token
        fwrite(t.name, sizeof(char), strlen(t.name), fp);

        //Write comma and space
        fwrite(", ", sizeof(char), 2, fp);

        //Write the type of the token
        fwrite(t.type, sizeof(char), strlen(t.type), fp);

        //Write comma and space
        fwrite(", ", sizeof(char), 2, fp);

        //Write the line of the token
        fprintf(fp, "%d", t.line);

        //Write \n
        fwrite(&enter, sizeof(char), 1, fp);
    } 
}


