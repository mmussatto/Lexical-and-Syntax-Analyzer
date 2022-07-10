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


void dealocate_follower(token* followers, int size_follower)
{
    int i;

    if(size_follower > 1)   //its a vector of followers
    {
        for(i = 0; i < size_follower; i++)
            free(followers[i].name);
        
    }    
    else    //its only one follower
        free(followers->name);

    free(followers);
}


void consume_until(vec_token* vec_tokens, token *curr_token, token* followers, int size_follower)
{
    int flg_sair = 0;
    int i;

    //Get the next token
    get_token_from_vector(vec_tokens, curr_token);

    //Consume tokens while hasn't reach EOF or found a follower
    while(strcmp(curr_token->name, "EOF") != 0 && !flg_sair)
    {
        //For each new token, test it with all followers
        for(i = 0; i < size_follower && !flg_sair; i++)
        {
            if(strcmp(curr_token->name,followers[i].name) == 0 ||
                strcmp(curr_token->type,followers[i].name) == 0)
            {
                //Found a follower, just break
                flg_sair = 1;
            }
        }
        
        if(!flg_sair)
            get_token_from_vector(vec_tokens, curr_token);
    }

    //Deallocate memory
    dealocate_follower(followers, size_follower);
}


void get_token_from_vector(vec_token* vec_tokens, token *curr_token)
{   
    char* substring;    //used to verify if the token is an error token

    //Increment the n_curr_token if it hasn't reach the end
    if(vec_tokens->n_curr_token != vec_tokens->size - 1)
    {
        vec_tokens->n_curr_token++;
    }

    //Dealocate memory from the last token
    if(curr_token->name != NULL && curr_token->type != NULL)
    {
        free(curr_token->name);
        free(curr_token->type);
    }

    //Verify if the current token is an error
    if(strlen(vec_tokens->tokens[vec_tokens->n_curr_token].type) > 14)
    {
        //Get the first letters ot the token's type
        substring = strndup(vec_tokens->tokens[vec_tokens->n_curr_token].type, 14); 

        while(strcmp(substring, "Lexical Error:") == 0) //runs through error tokens
        {
            vec_tokens->n_curr_token++; //get next token

            //Get the first letters ot the token's type
            substring = strndup(vec_tokens->tokens[vec_tokens->n_curr_token].type, 14); 
        }
      
        free(substring);    //deallocate the string
    }

    //Get the current token's properties
    curr_token->name = strdup(vec_tokens->tokens[vec_tokens->n_curr_token].name);
    curr_token->type = strdup(vec_tokens->tokens[vec_tokens->n_curr_token].type);
    curr_token->line = vec_tokens->tokens[vec_tokens->n_curr_token].line;
}


void ASD(vec_token* vec_tokens, synt_error_vec* vec_synt_error)
{
    //Create current token
    token *curr_token = malloc(1*sizeof(token));
    curr_token->name = NULL;
    curr_token->type = NULL;
    
    //Get first token from vector
    get_token_from_vector(vec_tokens, curr_token);

    //Call first rule 
    sytx_programa(vec_tokens, curr_token, vec_synt_error);

    //Check if last token is EOF and deallocate memory
    if (strcmp(curr_token->name, "EOF") == 0)
    {
        free(curr_token->name);
        free(curr_token->type);
        free(curr_token);
        return;
    }
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: EOF expected ", curr_token->line);
        free(curr_token->name);
        free(curr_token->type);
        free(curr_token);
        return;
    }
}


// 1.
void sytx_programa(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "program") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: Unexpected string, missing program ", curr_token->line);
        return;
    }
    
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: Unexpected string, missing identifier ", curr_token->line);
        return;
    }

    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: Missing semicolon ", curr_token->line);
        return;
    }

    sytx_corpo(vec_tokens, curr_token, vec_synt_error);
    
    if (strcmp(curr_token->name, ".") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: Missing final dot ", curr_token->line);
        return;
    }
        
    return;
    
}

// 2.
void sytx_corpo(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    
    //Creating followers
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(".");


    sytx_dc(vec_tokens, curr_token, vec_synt_error);

    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {
        add_synt_error(vec_synt_error, "Syntax Error: Missing begin ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 1);
        return;
    }

    sytx_comandos(vec_tokens, curr_token, vec_synt_error);    

    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {
        add_synt_error(vec_synt_error, "Syntax Error: Missing end clause ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 1);
        return;
    }

}

// 3.
void sytx_dc(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *temp = (token*) malloc(sizeof(token));
    temp->name = strdup(curr_token->name);

    token *follower = (token*) malloc(sizeof(token));
    follower->name = strdup("begin");
    
    sytx_dc_c(vec_tokens, curr_token, vec_synt_error);

    sytx_dc_v(vec_tokens, curr_token, vec_synt_error);

    sytx_dc_p(vec_tokens, curr_token, vec_synt_error);

    //It didnt change
    if(strcmp(temp->name, curr_token->name) == 0)
    {
        dealocate_follower(temp, 1);
        add_synt_error(vec_synt_error, "Syntax Error: Error in declaration ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 1);
    }
    else
    {
        dealocate_follower(temp, 1);
        dealocate_follower(follower, 1);
    }
}

// 4.
void sytx_dc_c(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(3*sizeof(token));
    follower[0].name = strdup("begin");
    follower[1].name = strdup("var");
    follower[2].name = strdup("procedure");


    if (strcmp(curr_token->name, "const") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);

        if (strcmp(curr_token->type, "identifier") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "Syntax Error: Expected identifier ", curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 3);
            return;
        }
          
        if (strcmp(curr_token->name, "=") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {
            add_synt_error(vec_synt_error, "Syntax Error: Missing '=' token ", curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 3);
            return;
        }

        if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        {
            get_token_from_vector(vec_tokens, curr_token);
            if (strcmp(curr_token->name, ";") == 0)
                get_token_from_vector(vec_tokens, curr_token);
            else 
            {
                add_synt_error(vec_synt_error, "Syntax Error: Missing expected semicolon ", curr_token->line);
                consume_until(vec_tokens, curr_token, follower, 3);
                return;
            }
        }
        else 
        {
            add_synt_error(vec_synt_error, curr_token->type, curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 3);
            return;
        }

        sytx_dc_c(vec_tokens, curr_token, vec_synt_error);
    }
}

// 5.
void sytx_dc_v(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(2*sizeof(token));
    follower[0].name = strdup("begin");
    follower[1].name = strdup("procedure");


    if (strcmp(curr_token->name, "var") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_variaveis(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, ":") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "Syntax Error: Expected double points ", curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 2);
            return;
        }
        
        if (strcmp(curr_token->name, "real") == 0 || strcmp(curr_token->name, "integer") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "Syntax Error: Expected variable type ", curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 2);
            return;
        }

        if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected semicolon ", curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 2);
            return;
        }

        sytx_dc_v(vec_tokens, curr_token, vec_synt_error);
    }
    else
    {
        dealocate_follower(follower, 2);
        return;   
    }
    
}

// 7.
void sytx_variaveis(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(2*sizeof(token));
    follower[0].name = strdup(":");
    follower[1].name = strdup(")");


    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Expected identifier ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 2);
        return;
    }
    dealocate_follower(follower, 2);
    sytx_mais_var(vec_tokens, curr_token, vec_synt_error);
}

// 8.
void sytx_mais_var(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(2*sizeof(token));
    follower[0].name = strdup(":");
    follower[1].name = strdup(")");


    if (strcmp(curr_token->name, ",") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        consume_until(vec_tokens, curr_token, follower, 2);
        sytx_variaveis(vec_tokens, curr_token, vec_synt_error);
    }
    else
    {
        dealocate_follower(follower, 2);
        return;
    }
}

// 9.
void sytx_dc_p(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup("begin");


    if (strcmp(curr_token->name, "procedure") == 0)
    {
            get_token_from_vector(vec_tokens, curr_token);

            if (strcmp(curr_token->type, "identifier") == 0)
                get_token_from_vector(vec_tokens, curr_token);
            else
            {
                add_synt_error(vec_synt_error, "Syntax Error: Expected identifier ", curr_token->line);
                consume_until(vec_tokens, curr_token, follower, 1);
                return;
            }

            sytx_parametros(vec_tokens, curr_token, vec_synt_error);

            if (strcmp(curr_token->name, ";") == 0)
                get_token_from_vector(vec_tokens, curr_token);
            else
            {
                add_synt_error(vec_synt_error, "Syntax Error: Missing expected semicolon ", curr_token->line);
                consume_until(vec_tokens, curr_token, follower, 1);
                return;
            }

            sytx_corpo_p(vec_tokens, curr_token, vec_synt_error);
        
            sytx_dc_p(vec_tokens, curr_token, vec_synt_error);  
    }  
    
    dealocate_follower(follower, 1);
}


// 10.
void sytx_parametros(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(";");


    if (strcmp(curr_token->name, "(") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);

        sytx_lista_par(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "Syntax Error: Missing closing parenthesis ", curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 1);
            return;
        }
    }

    dealocate_follower(follower, 2);
}

// 11.
void sytx_lista_par(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(")");


    sytx_variaveis(vec_tokens, curr_token, vec_synt_error);
    
    if (strcmp(curr_token->name, ":") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Expected double points ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 1);
        return;
    }

    if ((strcmp(curr_token->name, "real") == 0) || (strcmp(curr_token->name, "integer") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Expected variable type ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 1);
        return;
    }

    dealocate_follower(follower, 1);

    sytx_mais_par(vec_tokens, curr_token, vec_synt_error);
}

// 12.
void sytx_mais_par(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(")");
    

    if (strcmp(curr_token->name, ";") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        sytx_lista_par(vec_tokens, curr_token, vec_synt_error);
    }
    else
    {
        consume_until(vec_tokens, curr_token, follower, 1);
        return;    
    }

    dealocate_follower(follower, 1);

}

// 13.
void sytx_corpo_p(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(2*sizeof(token));
    follower[0].name = strdup("begin");
    follower[1].name = strdup("procedure");


    sytx_dc_loc(vec_tokens, curr_token, vec_synt_error);

    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Expected begin clause ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 2);
        return;
    }
        
    sytx_comandos(vec_tokens, curr_token, vec_synt_error);
    
    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Expected end clause ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 2);
        return;
    }
        
    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Missing expected semicolon ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 2);
        return;
    }

    dealocate_follower(follower, 2);
}

//14.
void sytx_dc_loc(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_dc_v(vec_tokens, curr_token, vec_synt_error);
}

// 15.
void sytx_lista_arg(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Creating followers
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(";");


    if (strcmp(curr_token->name, "(") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        sytx_argumentos(vec_tokens, curr_token, vec_synt_error);
        
        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected ')' ", curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 1);
        }
    }
    else
    {
        dealocate_follower(follower, 1);
        return;    
    }

    dealocate_follower(follower, 1);

}

// 16.
void sytx_argumentos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(")");

    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Expected identifier ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 1);
        return;
    }

    dealocate_follower(follower, 1);
    sytx_mais_ident(vec_tokens, curr_token, vec_synt_error);
}

// 17.
void sytx_mais_ident(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(")");

    if (strcmp(curr_token->name, ";") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        sytx_argumentos(vec_tokens, curr_token, vec_synt_error);
    }
    else
    {
        consume_until(vec_tokens, curr_token, follower, 1);
        return;
    }

    dealocate_follower(follower, 1);
}

// 18.
void sytx_pfalsa(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(";");

    if (strcmp(curr_token->name, "else") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        dealocate_follower(follower, 1);
        sytx_comandos(vec_tokens, curr_token, vec_synt_error);
    }
    else
    {
        consume_until(vec_tokens, curr_token, follower, 1);
        return;
    }
}

// 19.
void sytx_comandos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup("end");

    if ((strcmp(curr_token->name, "read")   == 0)       ||
        (strcmp(curr_token->name, "write")  == 0)       ||
        (strcmp(curr_token->name, "while")  == 0)       ||
        (strcmp(curr_token->name, "if")     == 0)       ||
        (strcmp(curr_token->type, "identifier") == 0)   ||
        (strcmp(curr_token->name, "begin")  == 0))
    {
        sytx_cmd(vec_tokens, curr_token, vec_synt_error);
        
        if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected semicolon ", curr_token->line);
            consume_until(vec_tokens, curr_token, follower, 1);
        }

        sytx_comandos(vec_tokens, curr_token, vec_synt_error);
    }
    else
    {
        dealocate_follower(follower, 1);
        return;
    }
}

// 20.
void sytx_cmd(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(sizeof(token));
    follower->name = strdup(";");

    //Read
    if (strcmp(curr_token->name, "read") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected '(' ", curr_token->line);
        
        sytx_variaveis(vec_tokens, curr_token, vec_synt_error);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected ')' ", curr_token->line);
        
    }   

    //Write
    else if (strcmp(curr_token->name, "write") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected '(' ", curr_token->line);
        
        sytx_variaveis(vec_tokens, curr_token, vec_synt_error);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected ')' ", curr_token->line);
        
    }

    //While
    else if (strcmp(curr_token->name, "while") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected '(' ", curr_token->line);
        
        sytx_condicao(vec_tokens, curr_token, vec_synt_error);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected ')' ", curr_token->line);

        if(strcmp(curr_token->name, "do") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected 'do' ", curr_token->line);

        sytx_cmd(vec_tokens, curr_token, vec_synt_error);
    }

    //If
    else if (strcmp(curr_token->name, "if") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_condicao(vec_tokens, curr_token, vec_synt_error);

        if(strcmp(curr_token->name, "then") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected 'then' ", curr_token->line);

        sytx_cmd(vec_tokens, curr_token, vec_synt_error);

        sytx_pfalsa(vec_tokens, curr_token, vec_synt_error);
        
    }

    //Ident
    else if (strcmp(curr_token->type, "identifier") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if (strcmp(curr_token->name, ":=") == 0)
        {
           get_token_from_vector(vec_tokens, curr_token);
           sytx_expressao(vec_tokens, curr_token, vec_synt_error);
        }
        else
            sytx_lista_arg(vec_tokens, curr_token, vec_synt_error);
        
    }

    //For
    else if (strcmp(curr_token->type, "identifier") == 0) {
        get_token_from_vector(vec_tokens, curr_token);
    
        if (strcmp(curr_token->name, ":=") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected ':=' ", curr_token->line);

        sytx_expressao(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, "to") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected 'to' ", curr_token->line);

        sytx_expressao(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, "do") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected 'do' ", curr_token->line);

        sytx_cmd(vec_tokens, curr_token, vec_synt_error);
    }

    //Begin
    else if (strcmp(curr_token->name, "begin") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_comandos(vec_tokens, curr_token, vec_synt_error);

        if(strcmp(curr_token->name, "end") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: Missing expected 'end' ", curr_token->line);
        
    }
    
    //Error
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Missing expected cmd ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 1);
        return;
    }

    dealocate_follower(follower, 1);
}


// 21.
void sytx_condicao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_expressao(vec_tokens, curr_token, vec_synt_error);

    sytx_relacao(vec_tokens, curr_token, vec_synt_error);

    sytx_expressao(vec_tokens, curr_token, vec_synt_error);
}

// 22.
void sytx_relacao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(5*sizeof(token));
    follower[0].name = strdup("+");
    follower[1].name = strdup("-");
    follower[2].name = strdup("identifier");
    follower[3].name = strdup("num_int");
    follower[4].name = strdup("num_real");

    if (strcmp(curr_token->name, "=") == 0)
        get_token_from_vector(vec_tokens, curr_token);

    else if (strcmp(curr_token->name, ">") == 0)
        get_token_from_vector(vec_tokens, curr_token);

    else if (strcmp(curr_token->name, "<") == 0)
        get_token_from_vector(vec_tokens, curr_token);
 
    else if (strcmp(curr_token->name, "<>") == 0)
        get_token_from_vector(vec_tokens, curr_token);

    else if (strcmp(curr_token->name, "<=") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    
    else if (strcmp(curr_token->name, ">=") == 0)
        get_token_from_vector(vec_tokens, curr_token);

    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Unrecognized comparator ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 4);
        return;
    }      

    dealocate_follower(follower, 4);
}

// 23.
void sytx_expressao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_termo(vec_tokens, curr_token, vec_synt_error);
    sytx_outros_termos(vec_tokens, curr_token, vec_synt_error);
}

// 24.
void sytx_op_un(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{       
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
        return;
}

// 25.
void sytx_outros_termos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_termo(vec_tokens, curr_token, vec_synt_error);

        sytx_outros_termos(vec_tokens, curr_token, vec_synt_error);
    }
    else    
        return;
}

// 26.
void sytx_op_ad(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(6*sizeof(token));
    follower[0].name = strdup("(");
    follower[1].name = strdup("+");
    follower[2].name = strdup("-");
    follower[3].name = strdup("identifier");
    follower[4].name = strdup("num_int");
    follower[5].name = strdup("num_real");

    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Unrecognized operator ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 6);
        return;
    }        

    dealocate_follower(follower, 6);
}

// 27.
void sytx_termo(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *temp = (token*) malloc(sizeof(token));
    temp->name = strdup(curr_token->name);

    token *follower = (token*) malloc(7*sizeof(token));
    follower[0].name = strdup(";");
    follower[1].name = strdup("+");
    follower[2].name = strdup("-");
    follower[3].name = strdup("identifier");
    follower[4].name = strdup("(");
    follower[5].name = strdup("num_int");
    follower[6].name = strdup("num_real");

    sytx_op_un(vec_tokens, curr_token, vec_synt_error);

    sytx_fator(vec_tokens, curr_token, vec_synt_error);

    sytx_mais_fatores(vec_tokens, curr_token, vec_synt_error);

    if(strcmp(temp->name, curr_token->name) == 0)
    {
        add_synt_error(vec_synt_error, "Syntax Error: Unrecognized term ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 7);
    }
    else
    {
        dealocate_follower(follower, 7);
    }
    
    dealocate_follower(temp, 1);
}

// 28.
void sytx_mais_fatores(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Op mul já está imbutido aqui
    if (strcmp(curr_token->name, "*") == 0 || strcmp(curr_token->name, "/") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        sytx_fator(vec_tokens, curr_token, vec_synt_error);
        sytx_mais_fatores(vec_tokens, curr_token, vec_synt_error);
    }
    else
        return;

}

// 30.
void sytx_fator(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(2*sizeof(token));
    follower[0].name = strdup("*");
    follower[1].name = strdup("/");

    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);

    else if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    
    else if (strcmp(curr_token->name, "(") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);

        sytx_expressao(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        {
            consume_until(vec_tokens, curr_token, follower, 2);
            add_synt_error(vec_synt_error, "Syntax Error: Missing closing parenthesis ", curr_token->line);
            return;
        }
    }

    dealocate_follower(follower, 2);
}

// 31.
void sytx_numero(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    token *follower = (token *) malloc(2*sizeof(token));
    follower[0].name = strdup("*");
    follower[1].name = strdup("/");

    if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Expected number ", curr_token->line);
        consume_until(vec_tokens, curr_token, follower, 2);
        return;
    }

    dealocate_follower(follower, 2);
}



