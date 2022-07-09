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

// 1.
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
    
    if (strcmp(curr_token->name, ".") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
        
    return;
    
}

// 2.
void sytx_corpo(vec_token* vec_tokens, token *curr_token)
{
    sytx_dc(vec_tokens, curr_token);

    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    sytx_comandos(vec_tokens, curr_token);    

    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

}

// 3.
void sytx_dc(vec_token* vec_tokens, token *curr_token)
{
    sytx_dc_c(vec_tokens, curr_token);

    sytx_dc_v(vec_tokens, curr_token);

    sytx_dc_p(vec_tokens, curr_token);
}

// 4.
void sytx_dc_c(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "const") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
        return;

    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
          
    if (strcmp(curr_token->name, "=") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim    

    if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
    
    sytx_dc_c(vec_tokens, curr_token);
}

// 5.
void sytx_dc_v(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "var") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else // lambda
        return;
    
    sytx_variaveis(vec_tokens, curr_token);

    if (strcmp(curr_token->name, ":") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
    
     if ((strcmp(curr_token->name, "real") == 0) || (strcmp(curr_token->name, "integer") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    sytx_dc_v(vec_tokens, curr_token);
}

// 7.
void sytx_variaveis(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    sytx_mais_var(vec_tokens, curr_token);
}

// 8.
void sytx_mais_var(vec_token* vec_tokens, token *curr_token)
{
     if (strcmp(curr_token->name, ",") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else // lambda
        return;
    
    sytx_variaveis(vec_tokens, curr_token);
}

// 9.
void sytx_dc_p(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "procedure") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else // lambda
        return;

    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    sytx_parametros(vec_tokens, curr_token);

    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    //sytx_corpo_p(vec_tokens, curr_token);

    sytx_dc_p(vec_tokens, curr_token);   
}


// 10.
void sytx_parametros(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "(") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
        return

    sytx_lista_par(vec_tokens, curr_token);

    if (strcmp(curr_token->name, ")") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
}

// 11.
void sytx_lista_par(vec_token* vec_tokens, token *curr_token)
{
    sytx_variaveis(vec_tokens, curr_token);
    
    if (strcmp(curr_token->name, ":") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

     if ((strcmp(curr_token->name, "real") == 0) || (strcmp(curr_token->name, "integer") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    sytx_mais_par(vec_tokens, curr_token);
    
}

// 12.
void sytx_mais_par(vec_token* vec_tokens, token *curr_token)
{
     if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else // lambda
        return;
    
    sytx_lista_par(vec_tokens, curr_token);
    
}

// 13.
void sytx_corpo_p(vec_token* vec_tokens, token *curr_token)
{
    sytx_dc_loc(vec_tokens, curr_token);

    if (strcmp(curr_token->name, "begin") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
        
    sytx_comandos(vec_tokens, curr_token);
    
    if (strcmp(curr_token->name, "end") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
        
    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
        

}

//14.
void sytx_dc_loc(vec_token* vec_tokens, token *curr_token)
{
    sytx_dc_v(vec_tokens, curr_token);
}

// 15.
void sytx_lista_arg(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "(") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else 
        return

    sytx_argumentos(vec_tokens, curr_token);

    if (strcmp(curr_token->name, ")") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
}

// 16.
void sytx_argumentos(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim

    sytx_mais_ident(vec_tokens, curr_token);
}

// 17.
void sytx_mais_ident(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, ";") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else // lambda
        return;

    sytx_argumentos(vec_tokens, curr_token);
}

// 18.
void sytx_pfalsa(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "else") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    else //Lambda
        return;

    sytx_comandos(vec_tokens, curr_token);

}

// 19.
void sytx_comandos(vec_token* vec_tokens, token *curr_token)
{
    if ((strcmp(curr_token->name, "read")   == 0)       ||
        (strcmp(curr_token->name, "write")  == 0)       ||
        (strcmp(curr_token->name, "while")  == 0)       ||
        (strcmp(curr_token->name, "if")     == 0)       ||
        (strcmp(curr_token->type, "identifier") == 0)  ||
        (strcmp(curr_token->name, "begin")  == 0))
    {
        sytx_cmd(vec_tokens, curr_token);
        
        if (strcmp(curr_token->name, ";") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim

        sytx_comandos(vec_tokens, curr_token);
    }    
}

// 20.
void sytx_cmd(vec_token* vec_tokens, token *curr_token)
{
    //Read
    if (strcmp(curr_token->name, "read") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim
        
        sytx_variaveis(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim
        
    }    

    //Write
    else if (strcmp(curr_token->name, "write") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim
        
        sytx_variaveis(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim
        
    }

    //While
    else if (strcmp(curr_token->name, "while") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, "(") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim
        
        sytx_condicao(vec_tokens, curr_token);
        
        if(strcmp(curr_token->name, ")") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim

        if(strcmp(curr_token->name, "do") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim

        sytx_cmd(vec_tokens, curr_token);
    }

    //If
    else if (strcmp(curr_token->name, "if") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_condicao(vec_tokens, curr_token);

        if(strcmp(curr_token->name, "then") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim

        sytx_cmd(vec_tokens, curr_token);

        sytx_pfalsa(vec_tokens, curr_token);
        
    }


    else if (strcmp(curr_token->type, "identifier") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        if (strcmp(curr_token->name, ":=") == 0)
        {
           get_token_from_vector(vec_tokens, curr_token);
           sytx_expressao(vec_tokens, curr_token);
        }
        else
            sytx_lista_arg(vec_tokens, curr_token);
        
    }

    //For
    else if (strcmp(curr_token->type, "identifier") == 0) {
        get_token_from_vector(vec_tokens, curr_token);
    
        if (strcmp(curr_token->name, ":=") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim

        sytx_expressao(vec_tokens, curr_token);

        if (strcmp(curr_token->name, "to") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim

        sytx_expressao(vec_tokens, curr_token);

        if (strcmp(curr_token->name, "do") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim

        sytx_cmd(vec_tokens, curr_token);
    }

    //Begin
    else if (strcmp(curr_token->name, "begin") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_comandos(vec_tokens, curr_token);

        if(strcmp(curr_token->name, "end") == 0)
            get_token_from_vector(vec_tokens, curr_token);
        //else 
            //deu ruim
        
    }
    
    //else
        //deu ruim

}


// 21.
void sytx_condicao(vec_token* vec_tokens, token *curr_token)
{
    sytx_expressao(vec_tokens, curr_token);

    sytx_relacao(vec_tokens, curr_token);

    sytx_expressao(vec_tokens, curr_token);
}

// 22.
void sytx_relacao(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "=") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else
        //deu ruim

    if (strcmp(curr_token->name, ">") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else
        //deu ruim

    if (strcmp(curr_token->name, "<") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else
        //deu ruim
    
    if (strcmp(curr_token->name, "<>") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else
        //deu ruim

    if (strcmp(curr_token->name, "<=") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else
        //deu ruim   
    
    if (strcmp(curr_token->name, ">=") == 0)
        get_token_from_vector(vec_tokens, curr_token);
    //else
        //deu ruim      
}

// 23.
void sytx_expressao(vec_token* vec_tokens, token *curr_token)
{
    sytx_termo(vec_tokens, curr_token);
    sytx_outros_termos(vec_tokens, curr_token);
}

// 24.
void sytx_op_un(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0)
            get_token_from_vector(vec_tokens, curr_token);
    else // lambda
        return;
}

// 25.
void sytx_outros_termos(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0){
        get_token_from_vector(vec_tokens, curr_token);
        
        sytx_termo(vec_tokens, curr_token);

        sytx_outros_termos(vec_tokens, curr_token);
    }
        
    return;
    
}

// 26.
void sytx_op_ad(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->name, "+") == 0 || strcmp(curr_token->name, "-") == 0)
            get_token_from_vector(vec_tokens, curr_token);
}

// 27.
void sytx_termo(vec_token* vec_tokens, token *curr_token)
{
    sytx_op_un(vec_tokens, curr_token);

    sytx_fator(vec_tokens, curr_token);

    sytx_mais_fatores(vec_tokens, curr_token);
}

// 28.
void sytx_mais_fatores(vec_token* vec_tokens, token *curr_token)
{
    //Op mul já está imbutido aqui
    if (strcmp(curr_token->name, "*") == 0 || strcmp(curr_token->name, "/") == 0)
    {
        get_token_from_vector(vec_tokens, curr_token);
        sytx_fator(vec_tokens, curr_token);
        sytx_mais_fatores(vec_tokens, curr_token);
    }
    
    return;

}

// 30.
void sytx_fator(vec_token* vec_tokens, token *curr_token)
{
    if (strcmp(curr_token->type, "identifier") == 0)
        get_token_from_vector(vec_tokens, curr_token);

    else if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);

    else if  (strcmp(curr_token->name, "(") == 0){
        get_token_from_vector(vec_tokens, curr_token);

        sytx_expressao(vec_tokens, curr_token);

        if (strcmp(curr_token->name, ")") == 0)
        get_token_from_vector(vec_tokens, curr_token);
        //else
            //deu ruim
    }

    //else 
        //deu ruim
}

// 31.
void sytx_numero(vec_token* vec_tokens, token *curr_token)
{
    if ((strcmp(curr_token->type, "num_int") == 0) || (strcmp(curr_token->type, "num_real") == 0))
        get_token_from_vector(vec_tokens, curr_token);
    //else 
        //deu ruim
}

