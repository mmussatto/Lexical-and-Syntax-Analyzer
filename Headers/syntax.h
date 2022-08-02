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

#pragma once

#include "Headers/lexical.h"
#include "Headers/sync.h"


/**
 * @brief Consume tokens until a synchronization token is found
 * 
 * @param vec_tokens vector containing all tokens from source code
 * @param curr_token current token
 * @param sync_stack stack containing the synchronization tokens
 * @return int position of the synchronization token found in the stack
 */
int consume_until(vec_token* vec_tokens, token *curr_token, stack* sync_stack);


/**
 * @brief Get the next token from token vector object
 * 
 * @param vec_tokens vector containing all tokens from source code
 * @param curr_token current token
 */
void get_token_from_vector(vec_token* vec_tokens, token *curr_token);


/**
 * @brief Function called by the main. Runs the syntax analyzer.
 * 
 * @param vec_tokens        vector containing all tokens from source code
 * @param vec_synt_error    vector containing all errors from the syntax analyzer
 * @return int 
 */
void ASD(vec_token* vec_tokens, synt_error_vec* vec_synt_error, stack* sync_stack);


/* ----- The funcitons below are a reflection of the syntax rules of the P-- language. ---- */

// 1.
void sytx_programa(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 2.
void sytx_corpo(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 3.
void sytx_dc(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 4.
void sytx_dc_c(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 5.
void sytx_dc_v(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 7.
void sytx_variaveis(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 8.
void sytx_mais_var(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 9.
void sytx_dc_p(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 10.
void sytx_parametros(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 11.
void sytx_lista_par(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 12.
void sytx_mais_par(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 13.
void sytx_corpo_p(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

//14.
void sytx_dc_loc(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

//15.
void sytx_lista_arg(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 16.
void sytx_argumentos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 17.
void sytx_mais_ident(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 18.
void sytx_pfalsa(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 19.
void sytx_comandos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 20.
void sytx_cmd(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 21.
void sytx_condicao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 22.
void sytx_relacao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 23.
void sytx_expressao(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 24.
void sytx_op_un(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 25.
void sytx_outros_termos(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 26.
void sytx_op_ad(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 27.
void sytx_termo(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 28.
void sytx_mais_fatores(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 30.
void sytx_fator(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);

// 31.
void sytx_numero(vec_token* vec_tokens, token *curr_token, synt_error_vec* vec_synt_error, stack *sync_stack);