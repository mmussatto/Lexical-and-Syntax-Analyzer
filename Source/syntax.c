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

void consume_until(vec_token* vec_tokens, token *curr_token, token follower)
{
    get_token_from_vector(vec_tokens, curr_token);

    //While it is not the follower AND it is not EOF
    while(strcmp(curr_token->type, follower.type) != 0 && strcmp(curr_token->name, follower.name) != 0
         && strcmp(curr_token->name, "EOF") != 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
    }
}

void sort_synt_error_vec(synt_error_vec *vec_synt_error){
    
    int i,j;
    int bigger;

    char *temp_desc;
    int temp_line;

    for (i = vec_synt_error->list_size - 1; i >= 0; i--){
        bigger = i;
        
        for (j = i - 1; j >= 0; j--){
            if(vec_synt_error->list_errors[j].line > vec_synt_error->list_errors[i].line)
                bigger = j;
        }

        if (i != bigger){
            temp_line = vec_synt_error->list_errors[bigger].line;
            temp_desc = vec_synt_error->list_errors[bigger].desc;

            vec_synt_error->list_errors[bigger].line = vec_synt_error->list_errors[i].line;
            vec_synt_error->list_errors[bigger].desc = vec_synt_error->list_errors[i].desc;

            vec_synt_error->list_errors[i].line = temp_line;
            vec_synt_error->list_errors[i].desc = temp_desc;
        }

    }
    
}


/****************************/
void write_error_file(FILE *fp, synt_error_vec *vec_synt_error, vec_token *vec_tokens)
{
    //Control variables
    int i;
    synt_error er;

    char *substring;

    //Run the tokens vector searching for errors
    for(i = 0; i< vec_tokens->size; i++)
    {
        if(strlen(vec_tokens->tokens[i].type) > 5)
        {
            substring = strndup(vec_tokens->tokens[i].type, 5);
            if(strcmp(substring, "ERROR") == 0)
                add_synt_error(vec_synt_error, vec_tokens->tokens[i].type, vec_tokens->tokens[i].line);

            free(substring);
        }
    }

    //FAZER  O SORT DO VETOR
    sort_synt_error_vec(vec_synt_error);

    //Traverse the tokens vector
    for(i = 0; i < vec_synt_error->list_size; i++)
    {   
        //Get the current token
        er = vec_synt_error->list_errors[i];

        //Write the name of the token
        fwrite(er.desc, sizeof(char), strlen(er.desc), fp);

        //Write comma and space
        fwrite(", ", sizeof(char), 2, fp);

        //Write the line of the problem
        fprintf(fp, "%d \n", er.line);
    } 
}
/****************************/

void get_token_from_vector(vec_token* vec_tokens, token *curr_token)
{   

    char* substring;

    if(vec_tokens->n_curr_token != vec_tokens->size)
    {
        vec_tokens->n_curr_token++;
    }
    
    if(curr_token->name != NULL && curr_token->type != NULL)
    {
        free(curr_token->name);
        free(curr_token->type);
    }
    
    if(strlen(vec_tokens->tokens[vec_tokens->n_curr_token].type) > 5)
    {
        substring = strndup(vec_tokens->tokens[vec_tokens->n_curr_token].type, 5);
        while(strcmp(substring, "ERROR") == 0){
            vec_tokens->n_curr_token++;
            substring = strndup(vec_tokens->tokens[vec_tokens->n_curr_token].type, 5);
        }
      
        free(substring);
    }
    
    curr_token->name = strdup(vec_tokens->tokens[vec_tokens->n_curr_token].name);
    curr_token->type = strdup(vec_tokens->tokens[vec_tokens->n_curr_token].type);
    curr_token->line = vec_tokens->tokens[vec_tokens->n_curr_token].line;
}

int ASD(vec_token* vec_tokens, synt_error_vec* vec_synt_error)
{
    token *curr_token = malloc(1*sizeof(token));
    curr_token->name = NULL;
    curr_token->type = NULL;
    
    get_token_from_vector(vec_tokens, curr_token);

    sytx_programa(vec_tokens, curr_token, vec_synt_error);

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

// 1.
void sytx_programa(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "program") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "ERROR: Unexpected string, missing program ", curr_token->line);
        return;
    }
    
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "ERROR: Unexpected string, missing identifier ", curr_token->line);
        return;
    }

    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "ERROR: Missing semicolon ", curr_token->line);
        return;
    }

    sytx_corpo(vec_tokens, curr_token, vec_synt_error);
    
    if (strcmp(curr_token->name, ".") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {   
        add_synt_error(vec_synt_error, "ERROR: Missing final dot ", curr_token->line);
        return;
    }
        
    return;
    
}

// 2.
void sytx_corpo(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_dc(vec_tokens, curr_token, vec_synt_error);

    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {
        add_synt_error(vec_synt_error, "ERROR: Missing begin ", curr_token->line);
        return;
    }

    sytx_comandos(vec_tokens, curr_token, vec_synt_error);    

    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
    {
        add_synt_error(vec_synt_error, "ERROR: Missing end clause ", curr_token->line);
        return;
    }

}

// 3.
void sytx_dc(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_dc_c(vec_tokens, curr_token, vec_synt_error);

    sytx_dc_v(vec_tokens, curr_token, vec_synt_error);

    sytx_dc_p(vec_tokens, curr_token, vec_synt_error);
}

// 4.
void sytx_dc_c(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "const") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);

        if (strcmp(curr_token->type, "identifier") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {   
            add_synt_error(vec_synt_error, "ERROR: Expected identifier ", curr_token->line);
            return;
        }
          
        if (strcmp(curr_token->name, "=") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {
            add_synt_error(vec_synt_error, "ERROR: Missing '=' token ", curr_token->line);
            return;
        }

        if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {
            add_synt_error(vec_synt_error, curr_token->type, curr_token->line);
            return;
        }

        if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
        {
            add_synt_error(vec_synt_error, "ERROR: Missing expected semicolon ", curr_token->line);
            return;
        }

        sytx_dc_c(vec_tokens, curr_token, vec_synt_error);
    }
}

// 5.
void sytx_dc_v(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "var") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_variaveis(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, ":") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "ERROR: Expected double points ", curr_token->line);
            return;
        }
        
        if (strcmp(curr_token->name, "real") == 0 || strcmp(curr_token->name, "integer") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "ERROR: Expected variable type ", curr_token->line);
            return;
        }

        if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "ERROR: Missing expected semicolon ", curr_token->line);
            return;
        }

        sytx_dc_v(vec_tokens, curr_token, vec_synt_error);
    }
    else
        return;   

    
}

// 7.
void sytx_variaveis(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Expected identifier ", curr_token->line);
        return;
    }
    sytx_mais_var(vec_tokens, curr_token, vec_synt_error);
}

// 8.
void sytx_mais_var(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, ",") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        sytx_variaveis(vec_tokens, curr_token, vec_synt_error);
    }
    else
        return;
}

// 9.
void sytx_dc_p(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "procedure") == 0)
    {
            get_token_from_vector(vec_tokens, curr_token);

            if (strcmp(curr_token->type, "identifier") == 0)
                get_token_from_vector(vec_tokens, curr_token);
            else
            {
                add_synt_error(vec_synt_error, "ERROR: Expected identifier ", curr_token->line);
                return;
            }

            sytx_parametros(vec_tokens, curr_token, vec_synt_error);

            if (strcmp(curr_token->name, ";") == 0)
                get_token_from_vector(vec_tokens, curr_token);
            else
            {
                add_synt_error(vec_synt_error, "ERROR: Missing expected semicolon ", curr_token->line);
                return;
            }

            sytx_corpo_p(vec_tokens, curr_token, vec_synt_error);
        
            sytx_dc_p(vec_tokens, curr_token, vec_synt_error);  
    }   
}


// 10.
void sytx_parametros(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "(") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);

        sytx_lista_par(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else
        {
            add_synt_error(vec_synt_error, "ERROR: Missing closing parenthesis ", curr_token->line);
            return;
        }
    }
}

// 11.
void sytx_lista_par(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_variaveis(vec_tokens, curr_token, vec_synt_error);
    
    if (strcmp(curr_token->name, ":") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Expected double points ", curr_token->line);
        return;
    }

    if ((strcmp(curr_token->name, "real") == 0) || (strcmp(curr_token->name, "integer") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Expected variable type ", curr_token->line);
        return;
    }

    sytx_mais_par(vec_tokens, curr_token, vec_synt_error);
    
}

// 12.
void sytx_mais_par(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, ";") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        sytx_lista_par(vec_tokens, curr_token, vec_synt_error);
    }
    else
        return;    
}

// 13.
void sytx_corpo_p(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_dc_loc(vec_tokens, curr_token, vec_synt_error);

    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Expected begin clause ", curr_token->line);
        return;
    }
        
    sytx_comandos(vec_tokens, curr_token, vec_synt_error);
    
    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Expected end clause ", curr_token->line);
        return;
    }
        
    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Missing expected semicolon ", curr_token->line);
        return;
    }
}

//14.
void sytx_dc_loc(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_dc_v(vec_tokens, curr_token, vec_synt_error);
}

// 15.
void sytx_lista_arg(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "(") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);

        sytx_argumentos(vec_tokens, curr_token, vec_synt_error);
        
        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected ')' ", curr_token->line);
    }
    else 
        return;    
}

// 16.
void sytx_argumentos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Expected identifier ", curr_token->line);
        return;
    }

    sytx_mais_ident(vec_tokens, curr_token, vec_synt_error);
}

// 17.
void sytx_mais_ident(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, ";") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        sytx_argumentos(vec_tokens, curr_token, vec_synt_error);
    }
    else
        return;
}

// 18.
void sytx_pfalsa(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if (strcmp(curr_token->name, "else") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        sytx_comandos(vec_tokens, curr_token, vec_synt_error);
    }
    else
        return;
}

// 19.
void sytx_comandos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if ((strcmp(curr_token->name, "read")   == 0)       ||
        (strcmp(curr_token->name, "write")  == 0)       ||
        (strcmp(curr_token->name, "while")  == 0)       ||
        (strcmp(curr_token->name, "if")     == 0)       ||
        (strcmp(curr_token->type, "identifier") == 0)  ||
        (strcmp(curr_token->name, "begin")  == 0))
    {
        sytx_cmd(vec_tokens, curr_token, vec_synt_error);
        
        if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected semicolon ", curr_token->line);

        sytx_comandos(vec_tokens, curr_token, vec_synt_error);
    }
    else
        return;
    
}

// 20.
void sytx_cmd(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    //Read
    if (strcmp(curr_token->name, "read") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected '(' ", curr_token->line);
        
        sytx_variaveis(vec_tokens, curr_token, vec_synt_error);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected ')' ", curr_token->line);
        
    }    
    //Write
    else if (strcmp(curr_token->name, "write") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected '(' ", curr_token->line);
        
        sytx_variaveis(vec_tokens, curr_token, vec_synt_error);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected ')' ", curr_token->line);
        
    }

    //While
    else if (strcmp(curr_token->name, "while") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected '(' ", curr_token->line);
        
        sytx_condicao(vec_tokens, curr_token, vec_synt_error);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected ')' ", curr_token->line);

        if(strcmp(curr_token->name, "do") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected 'do' ", curr_token->line);

        sytx_cmd(vec_tokens, curr_token, vec_synt_error);
    }

    //If
    else if (strcmp(curr_token->name, "if") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_condicao(vec_tokens, curr_token, vec_synt_error);

        if(strcmp(curr_token->name, "then") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected 'then' ", curr_token->line);

        sytx_cmd(vec_tokens, curr_token, vec_synt_error);

        sytx_pfalsa(vec_tokens, curr_token, vec_synt_error);
        
    }
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
            add_synt_error(vec_synt_error, "ERROR: Missing expected ':=' ", curr_token->line);

        sytx_expressao(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, "to") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected 'to' ", curr_token->line);

        sytx_expressao(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, "do") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected 'do' ", curr_token->line);

        sytx_cmd(vec_tokens, curr_token, vec_synt_error);
    }

    //Begin
    else if (strcmp(curr_token->name, "begin") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_comandos(vec_tokens, curr_token, vec_synt_error);

        if(strcmp(curr_token->name, "end") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        else 
            add_synt_error(vec_synt_error, "ERROR: Missing expected 'end' ", curr_token->line);
        
    }
    
    else
        add_synt_error(vec_synt_error, "ERROR: Missing expected cmd ", curr_token->line);

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
        add_synt_error(vec_synt_error, "ERROR: Unrecognized comparator ", curr_token->line);
        return;
    }      
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
    else // lambda
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
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else
        add_synt_error(vec_synt_error, "ERROR: Unrecognized operator ", curr_token->line);
        
}

// 27.
void sytx_termo(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    sytx_op_un(vec_tokens, curr_token, vec_synt_error);

    sytx_fator(vec_tokens, curr_token, vec_synt_error);

    sytx_mais_fatores(vec_tokens, curr_token, vec_synt_error);
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
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);

    else if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    
    else if  (strcmp(curr_token->name, "(") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);

        sytx_expressao(vec_tokens, curr_token, vec_synt_error);

        if (strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        {
            add_synt_error(vec_synt_error, "ERROR: Missing closing parenthesis ", curr_token->line);
            return;
        }
    }
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Unexpected factor ", curr_token->line);
        return;
    }
}

// 31.
void sytx_numero(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error)
{
    if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    else
    {
        add_synt_error(vec_synt_error, "ERROR: Expected number ", curr_token->line);
        return;
    }
}



