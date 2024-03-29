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


int consume_until(vec_token* vec_tokens, token *curr_token, stack* sync_stack)
{
    int i;

    //Consume tokens while hasn't reach EOF or found a follower
    while(strcmp(curr_token->name, "EOF") != 0)
    {
        //For each new token, test it with all followers
        for(i = sync_stack->curr_size-1 ; i >= 0; i--)
        {
            if(strcmp(curr_token->name,  sync_stack->list_tokens[i]) == 0 ||
                strcmp(curr_token->type, sync_stack->list_tokens[i]) == 0)
            {
                return i;
            }
        }   
        get_token_from_vector(vec_tokens, curr_token);
    }

    return -1;

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


/*------------------------------ Parser ------------------------------*/

void ASD(vec_token* vec_tokens, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    //Create current token
    token *curr_token = malloc(1*sizeof(token));
    curr_token->name = NULL;
    curr_token->type = NULL;
    
    //Get first token from vector
    get_token_from_vector(vec_tokens, curr_token);

    //Call first rule 
    sytx_programa(vec_tokens, curr_token, vec_synt_error, sync_stack);

    //Check if last token is EOF and deallocate memory
    if (strcmp(curr_token->name, "EOF") == 0)
    {
        free(curr_token->name);
        free(curr_token->type);
        free(curr_token);
    }
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Compilation Failed ", curr_token->line);
        free(curr_token->name);
        free(curr_token->type);
        free(curr_token);
    }
}

// 1.
void sytx_programa(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{

    if (strcmp(curr_token->name, "program") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   //panic mode  
        add_synt_error(vec_synt_error, "Syntax Error: expected \"program\" ", curr_token->line);

        //push the next token of this rule (function will not return if this token is found)
        sync_push(sync_stack, "identifier");

        //position of the follower token in the sync_stack
        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);    

        //valid sync tokens. Numbers lower than this will return the function
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  //pop identifier

        //verifies if the function has to continue or return
        if(sync_token_position < sync_valid_positions)
            return;
        
    }
    

    if (strcmp(curr_token->type, "identifier") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected an identifier ", curr_token->line);

        sync_push(sync_stack, ";");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
        
    }
    

    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \";\" ", curr_token->line);

        
        sync_push(sync_stack, "const");
        sync_push(sync_stack, "var");
        sync_push(sync_stack, "procedure");
        sync_push(sync_stack, "begin");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 4;

        sync_pop(sync_stack, 4);  

        if(sync_token_position < sync_valid_positions)
            return;
        
    }


    sync_push(sync_stack, ".");

    sytx_corpo(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);    //pop "."

    
    if (strcmp(curr_token->name, ".") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
        add_synt_error(vec_synt_error, "Syntax Error: expected \".\" ", curr_token->line);
        
    return;
}

// 2.
void sytx_corpo(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{

    sync_push(sync_stack, "begin"); //push begin

    sytx_dc(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);        //pop begin


    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {
        add_synt_error(vec_synt_error, "Syntax Error: expected \"begin\" ", curr_token->line);

        
        sync_push(sync_stack, "read");
        sync_push(sync_stack, "write");
        sync_push(sync_stack, "while");
        sync_push(sync_stack, "if");
        sync_push(sync_stack, "identifier");
        sync_push(sync_stack, "begin");
        sync_push(sync_stack, "for");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 7;

        sync_pop(sync_stack, 7);  

        if(sync_token_position < sync_valid_positions)
            return;
    }
    

    sync_push(sync_stack, "end");

    sytx_comandos(vec_tokens, curr_token, vec_synt_error, sync_stack);   

    sync_pop(sync_stack, 1);


    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
        add_synt_error(vec_synt_error, "Syntax Error: expected \"end\" ", curr_token->line);
}

// 3.
void  sytx_dc(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{

    sync_push(sync_stack, "procedure");
    sync_push(sync_stack, "var");
    
    sytx_dc_c(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);    //teoricamente retirando var

    sytx_dc_v(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);    //teoricamente retirando procedure

    sytx_dc_p(vec_tokens, curr_token, vec_synt_error, sync_stack);

}

// 4.
void sytx_dc_c(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{

    if (strcmp(curr_token->name, "const") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        
        sync_push(sync_stack, "identifier");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
        
        //Error comes down here because the rule could be lamda (not expecting a "const" here)
        add_synt_error(vec_synt_error, "Syntax Error: expected \"const\" ", curr_token->line);
    }


    if (strcmp(curr_token->type, "identifier") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected an identifier ", curr_token->line);
        
        sync_push(sync_stack, "=");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    if (strcmp(curr_token->name, "=") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \"=\" ", curr_token->line);
        
        sync_push(sync_stack, "num_int");
        sync_push(sync_stack, "num_real");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 2;

        sync_pop(sync_stack, 2);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \"real\" or \"integer\" ", curr_token->line);
        
        sync_push(sync_stack, ";");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \";\" ", curr_token->line);

        
        sync_push(sync_stack, "const");
        
        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    sytx_dc_c(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 5.
void sytx_dc_v(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, "var") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        sync_push(sync_stack, "identifier");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;

        //Error comes down here because the rule could be lamda (not expecting a "var" here)
        add_synt_error(vec_synt_error, "Syntax Error: expected \"var\" ", curr_token->line);
    }


    sync_push(sync_stack, ":");

    sytx_variaveis(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);  //pop ":"


    if (strcmp(curr_token->name, ":") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \":\" ", curr_token->line-1);
        
        sync_push(sync_stack, "real");
        sync_push(sync_stack, "integer");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 2;

        sync_pop(sync_stack, 2);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    if (strcmp(curr_token->name, "real") == 0 || strcmp(curr_token->name, "integer") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \"real\" or \"integer\" ", curr_token->line);
        
        sync_push(sync_stack, ";");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \";\" ", curr_token->line);

        sync_push(sync_stack, "var");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    sytx_dc_v(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 7.
void sytx_variaveis(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->type, "identifier") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected an identifier ", curr_token->line);

        
        sync_push(sync_stack, ",");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;        
    }


    sytx_mais_var(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 8.
void sytx_mais_var(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, ",") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {    
        sync_push(sync_stack, "identifier");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
         
        //Error comes down here because the rule could be lamda (not expecting a comma here)
        add_synt_error(vec_synt_error, "Syntax Error: expected \",\" ", curr_token->line);
    }


    sytx_variaveis(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 9.
void sytx_dc_p(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, "procedure") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        sync_push(sync_stack, "identifier");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
         
        //Error comes down here because the rule could be lamda (not expecting a colon here)
        add_synt_error(vec_synt_error, "Syntax Error: expected \"procedure\" ", curr_token->line);
    }


    if (strcmp(curr_token->type, "identifier") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected an identifier ", curr_token->line);

        sync_push(sync_stack, "(");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    sync_push(sync_stack, ";");

    sytx_parametros(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1); 


    if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        sync_push(sync_stack, "var");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
         
        //Error comes down here because the rule could be lamda (not expecting parameters)
        add_synt_error(vec_synt_error, "Syntax Error: expected \";\" ", curr_token->line);
    }


    sync_push(sync_stack, "procedure");

    sytx_corpo_p(vec_tokens, curr_token, vec_synt_error, sync_stack); 

    sync_pop(sync_stack, 1); 


    sytx_dc_p(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 10.
void sytx_parametros(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        sync_push(sync_stack, "identifier");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
         
        //Error comes down here because the rule could be lamda (not expecting parameters)
        add_synt_error(vec_synt_error, "Syntax Error: expected \"(\" ", curr_token->line);
    }


    sync_push(sync_stack, ")");

    sytx_lista_par(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);  


    if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \")\" ", curr_token->line);
    }
}

// 11.
void sytx_lista_par(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    sync_push(sync_stack, ":");

    sytx_variaveis(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);


    if (strcmp(curr_token->name, ":") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \":\" ", curr_token->line);
        
        sync_push(sync_stack, "real");
        sync_push(sync_stack, "integer");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 2;

        sync_pop(sync_stack, 2);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    if (strcmp(curr_token->name, "real") == 0 || strcmp(curr_token->name, "integer") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \"rael\" \"identifier\" ", curr_token->line);
        
        sync_push(sync_stack, ";");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    sytx_mais_par(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 12.
void sytx_mais_par(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {    
        sync_push(sync_stack, "identifier");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
         
        //Error comes down here because the rule could be lamda (not expecting a comma here)
        add_synt_error(vec_synt_error, "Syntax Error: expected \";\" ", curr_token->line);
    }


    sytx_lista_par(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 13.
void sytx_corpo_p(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    sync_push(sync_stack, "begin");

    sytx_dc_loc(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);  


    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {
        add_synt_error(vec_synt_error, "Syntax Error: expected \"begin\" ", curr_token->line);
        
        sync_push(sync_stack, "read");
        sync_push(sync_stack, "write");
        sync_push(sync_stack, "while");
        sync_push(sync_stack, "if");
        sync_push(sync_stack, "identifier");
        sync_push(sync_stack, "begin");
        sync_push(sync_stack, "for");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 7;

        sync_pop(sync_stack, 7);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    sync_push(sync_stack, "end");

    sytx_comandos(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1); 


    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected \"end\" ", curr_token->line);

        sync_push(sync_stack, ";");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;         
    }


    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else  
        add_synt_error(vec_synt_error, "Syntax Error: expected \";\" ", curr_token->line);      
}

//14.
void sytx_dc_loc(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    sytx_dc_v(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 15.
void sytx_lista_arg(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, "(") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        sync_push(sync_stack, "identifier");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
         
        //Error comes down here because the rule could be lamda (not expecting parameters)
        add_synt_error(vec_synt_error, "Syntax Error: expected \"(\" ", curr_token->line);
    }


    sync_push(sync_stack, ")");

    sytx_argumentos(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 1);  


    if (strcmp(curr_token->name, ")") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
        add_synt_error(vec_synt_error, "Syntax Error: Missing expected close parenthesis ", curr_token->line);
}

// 16.
void sytx_argumentos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "Syntax Error: expected an identifier ", curr_token->line);

        sync_push(sync_stack, ",");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;
    }


    sytx_mais_ident(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 17.
void sytx_mais_ident(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        sync_push(sync_stack, "identifier");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 1;

        sync_pop(sync_stack, 1);  

        if(sync_token_position < sync_valid_positions)
            return;

        //Error comes down here because the rule could be lamda (not expecting a comma here)
        add_synt_error(vec_synt_error, "Syntax Error: expected \";\" ", curr_token->line);
    }


    sytx_argumentos(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 18.
void sytx_pfalsa(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, "else") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {
        sync_push(sync_stack, "read");
        sync_push(sync_stack, "write");
        sync_push(sync_stack, "while");
        sync_push(sync_stack, "if");
        sync_push(sync_stack, "identifier");
        sync_push(sync_stack, "begin");
        sync_push(sync_stack, "for");

        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size - 7;

        sync_pop(sync_stack, 7);  

        if(sync_token_position < sync_valid_positions)
            return;

        //Error comes down here because the rule could be lamda (not expecting a comma here)
        add_synt_error(vec_synt_error, "Syntax Error: expected \"else\" ", curr_token->line);
    }


    sytx_cmd(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 19.
void sytx_comandos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if ((strcmp(curr_token->name, "read")   == 0)       ||
        (strcmp(curr_token->name, "write")  == 0)       ||
        (strcmp(curr_token->name, "while")  == 0)       ||
        (strcmp(curr_token->name, "if")     == 0)       ||
        (strcmp(curr_token->type, "identifier") == 0)   ||
        (strcmp(curr_token->name, "for")    == 0)       ||
        (strcmp(curr_token->name, "begin")  == 0))
    {
        sync_push(sync_stack, ";");

        sytx_cmd(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);


        if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {
            sync_push(sync_stack, "read");
            sync_push(sync_stack, "write");
            sync_push(sync_stack, "while");
            sync_push(sync_stack, "if");
            sync_push(sync_stack, "identifier");
            sync_push(sync_stack, "begin");
            sync_push(sync_stack, "for");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 7;

            sync_pop(sync_stack, 7);

            if(sync_token_position < sync_valid_positions)
                return;

            //Error comes down here because the rule could be lamda (not expecting a comma here)
            add_synt_error(vec_synt_error, "Syntax Error: expected \";\" ", curr_token->line);
        }


        sytx_comandos(vec_tokens, curr_token, vec_synt_error, sync_stack);
    }
}

// 20.
void sytx_cmd(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    //Read
    if (strcmp(curr_token->name, "read") == 0){
        get_token_from_vector(vec_tokens, curr_token);

        if (strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "Syntax Error: expected \"(\" ", curr_token->line);

            sync_push(sync_stack, "identifier");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 1;

            sync_pop(sync_stack, 1);  

            if(sync_token_position < sync_valid_positions)
                return;  
        }

        sync_push(sync_stack, ")");

        sytx_variaveis(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);  


        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: expected \")\" ", curr_token->line);
    }   

    //Write
    else if (strcmp(curr_token->name, "write") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if (strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "Syntax Error: expected \"(\" ", curr_token->line);

            sync_push(sync_stack, "identifier");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 1;

            sync_pop(sync_stack, 1);  

            if(sync_token_position < sync_valid_positions)
                return;
        }


        sync_push(sync_stack, ")");

        sytx_variaveis(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);  


        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: expected \")\" ", curr_token->line);
    }

    //While
    else if (strcmp(curr_token->name, "while") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if (strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "Syntax Error: expected \"(\" ", curr_token->line);

            sync_push(sync_stack, "identifier");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 1;

            sync_pop(sync_stack, 1);  

            if(sync_token_position < sync_valid_positions)
                return;
        }


        sync_push(sync_stack, ")");

        sytx_condicao(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);  


        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "Syntax Error: expected \")\" ", curr_token->line);
            
            sync_push(sync_stack, "do");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 1;

            sync_pop(sync_stack, 1);  

            if(sync_token_position < sync_valid_positions)
                return; 
        }


        if (strcmp(curr_token->name, "do") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {
            add_synt_error(vec_synt_error, "Syntax Error: expected \"do\" ", curr_token->line);
            
            sync_push(sync_stack, "read");
            sync_push(sync_stack, "write");
            sync_push(sync_stack, "while");
            sync_push(sync_stack, "if");
            sync_push(sync_stack, "identifier");
            sync_push(sync_stack, "begin");
            sync_push(sync_stack, "for");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 7;

            sync_pop(sync_stack, 7);  

            if(sync_token_position < sync_valid_positions)
                return;
        }


        sytx_cmd(vec_tokens, curr_token, vec_synt_error, sync_stack);
    }

    //If
    else if (strcmp(curr_token->name, "if") == 0){
        get_token_from_vector(vec_tokens, curr_token);


        sync_push(sync_stack, "then");
        
        sytx_condicao(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);


        if (strcmp(curr_token->name, "then") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {
            add_synt_error(vec_synt_error, "Syntax Error: expected \"then\" ", curr_token->line);
            
            sync_push(sync_stack, "read");
            sync_push(sync_stack, "write");
            sync_push(sync_stack, "while");
            sync_push(sync_stack, "if");
            sync_push(sync_stack, "identifier");
            sync_push(sync_stack, "begin");
            sync_push(sync_stack, "for");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 7;

            sync_pop(sync_stack, 7);

            if(sync_token_position < sync_valid_positions)
                return;
        }


        sync_push(sync_stack, "else");

        sytx_cmd(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);


        sytx_pfalsa(vec_tokens, curr_token, vec_synt_error, sync_stack);
    }

    //Ident
    else if (strcmp(curr_token->type, "identifier") == 0){
        get_token_from_vector(vec_tokens, curr_token);

        if (strcmp(curr_token->name, ":=") == 0)
        {
           get_token_from_vector(vec_tokens, curr_token);
           sytx_expressao(vec_tokens, curr_token, vec_synt_error, sync_stack);
        }
        else 
            sytx_lista_arg(vec_tokens, curr_token, vec_synt_error, sync_stack);    
    }

    //For
    else if (strcmp(curr_token->name, "for") == 0) {
        get_token_from_vector(vec_tokens, curr_token);

        if (strcmp(curr_token->type, "identifier") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "Syntax Error: expected an identifier ", curr_token->line);

            sync_push(sync_stack, ":=");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 1;

            sync_pop(sync_stack, 1);  

            if(sync_token_position < sync_valid_positions)
                return;
        }


        if (strcmp(curr_token->name, ":=") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "Syntax Error: expected \":=\" ", curr_token->line);
            
            sync_push(sync_stack, "+");
            sync_push(sync_stack, "-");
            sync_push(sync_stack, "identifier");
            sync_push(sync_stack, "integer");
            sync_push(sync_stack, "real");
            sync_push(sync_stack, "(");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 6;

            sync_pop(sync_stack, 6);  

            if(sync_token_position < sync_valid_positions)
                return;
        }


        sync_push(sync_stack, "to");

        sytx_expressao(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);


        if (strcmp(curr_token->name, "to") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "Syntax Error: expected \"to\" ", curr_token->line);

            sync_push(sync_stack, "+");
            sync_push(sync_stack, "-");
            sync_push(sync_stack, "identifier");
            sync_push(sync_stack, "integer");
            sync_push(sync_stack, "real");
            sync_push(sync_stack, "(");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 6;

            sync_pop(sync_stack, 6);  

            if(sync_token_position < sync_valid_positions)
                return;  
        }


        sync_push(sync_stack, "do");

        sytx_expressao(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);


        if (strcmp(curr_token->name, "do") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {
            add_synt_error(vec_synt_error, "Syntax Error: expected \"do\" ", curr_token->line);
        
            sync_push(sync_stack, "read");
            sync_push(sync_stack, "write");
            sync_push(sync_stack, "while");
            sync_push(sync_stack, "if");
            sync_push(sync_stack, "identifier");
            sync_push(sync_stack, "begin");
            sync_push(sync_stack, "for");

            int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
            int sync_valid_positions = sync_stack->curr_size - 7;

            sync_pop(sync_stack, 7);

            if(sync_token_position < sync_valid_positions)
                return;
        }


        sytx_cmd(vec_tokens, curr_token, vec_synt_error, sync_stack);
    }

    //Begin
    else if (strcmp(curr_token->name, "begin") == 0){
        get_token_from_vector(vec_tokens, curr_token);


        sync_push(sync_stack, "end");
        
        sytx_comandos(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);


        if(strcmp(curr_token->name, "end") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "Syntax Error: expected \"end\" ", curr_token->line);
    }
    
    //Error
    else
    {
        int sync_token_position = consume_until(vec_tokens, curr_token, sync_stack);
        int sync_valid_positions = sync_stack->curr_size-1;
 
        if(sync_token_position < sync_valid_positions)
            return;

        //Error comes down here because the rule could be lamda (not expecting a comma here)
        add_synt_error(vec_synt_error, "Syntax Error: expected a command ", curr_token->line);
    }
}

// 21.
void sytx_condicao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    //First of <relacao>
    sync_push(sync_stack, "=");
    sync_push(sync_stack, "<>");
    sync_push(sync_stack, ">=");
    sync_push(sync_stack, "<=");
    sync_push(sync_stack, ">");
    sync_push(sync_stack, "<");

    sytx_expressao(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 6);

    //First of <expressao>
    sync_push(sync_stack, "+");
    sync_push(sync_stack, "-");
    sync_push(sync_stack, "identifier");
    sync_push(sync_stack, "integer");
    sync_push(sync_stack, "real");
    sync_push(sync_stack, "(");

    sytx_relacao(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 6);

    sytx_expressao(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 22.
void sytx_relacao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
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
        add_synt_error(vec_synt_error, "Syntax Error: expected a comparator ", curr_token->line);
        consume_until(vec_tokens, curr_token, sync_stack);
        return;
    }      
}

// 23.
void sytx_expressao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    sync_push(sync_stack, "+");
    sync_push(sync_stack, "-");

    sytx_termo(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 2);

    sytx_outros_termos(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 24.
void sytx_op_un(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{       
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
        return;
}

// 25.
void sytx_outros_termos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sync_push(sync_stack, "+");
        sync_push(sync_stack, "-");

        sytx_termo(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 2);

        sytx_outros_termos(vec_tokens, curr_token, vec_synt_error, sync_stack);
    }
    else    
        return;
}

// 26.
void sytx_op_ad(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: expected \"+\" or \"-\" ", curr_token->line);
        consume_until(vec_tokens, curr_token, sync_stack);
    }        
}

// 27.
void sytx_termo(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{

    sytx_op_un(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_push(sync_stack, "*");
    sync_push(sync_stack, "/");

    sytx_fator(vec_tokens, curr_token, vec_synt_error, sync_stack);

    sync_pop(sync_stack, 2);

    sytx_mais_fatores(vec_tokens, curr_token, vec_synt_error, sync_stack);
}

// 28.
void sytx_mais_fatores(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    //the <op_mul> is included on this if clause
    if (strcmp(curr_token->name, "*") == 0 || strcmp(curr_token->name, "/") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);

        sytx_fator(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sytx_mais_fatores(vec_tokens, curr_token, vec_synt_error, sync_stack);
    }
    else
        return;
}

// 30.
void sytx_fator(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);

    else if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    
    else if (strcmp(curr_token->name, "(") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);


        sync_push(sync_stack, ")");

        sytx_expressao(vec_tokens, curr_token, vec_synt_error, sync_stack);

        sync_pop(sync_stack, 1);


        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "Syntax Error: expected \")\" ", curr_token->line);
            consume_until(vec_tokens, curr_token, sync_stack);
        }
    }

    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: Missing term in <fator> rule ", curr_token->line);
        consume_until(vec_tokens, curr_token, sync_stack);
    }
}

// 31.
void sytx_numero(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack)
{
    if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "Syntax Error: expected a number", curr_token->line);
        consume_until(vec_tokens, curr_token, sync_stack);
    }
}



