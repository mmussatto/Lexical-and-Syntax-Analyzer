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


void get_token_from_vector(vec_token* vec_tokens, token *curr_token);

int ASD(vec_token* vec_tokens);

// 1.
void sytx_programa(vec_token* vec_tokens, token *curr_token);

// 2.
void sytx_corpo(vec_token* vec_tokens, token *curr_token);

// 3.
void sytx_dc(vec_token* vec_tokens, token *curr_token);

// 4.
void sytx_dc_c(vec_token* vec_tokens, token *curr_token);

// 5.
void sytx_dc_v(vec_token* vec_tokens, token *curr_token);

// 7.
void sytx_variaveis(vec_token* vec_tokens, token *curr_token);

// 8.
void sytx_mais_var(vec_token* vec_tokens, token *curr_token);

// 9.
void sytx_dc_p(vec_token* vec_tokens, token *curr_token);

// 10.
void sytx_parametros(vec_token* vec_tokens, token *curr_token);

// 11.
void sytx_lista_par(vec_token* vec_tokens, token *curr_token);

// 12.
void sytx_mais_par(vec_token* vec_tokens, token *curr_token);

// 13.
void sytx_corpo_p(vec_token* vec_tokens, token *curr_token);

//14.
void sytx_dc_loc(vec_token* vec_tokens, token *curr_token);

//15.
void sytx_lista_arg(vec_token* vec_tokens, token *curr_token);

// 16.
void sytx_argumentos(vec_token* vec_tokens, token *curr_token);

// 17.
void sytx_mais_ident(vec_token* vec_tokens, token *curr_token);

// 18.
void sytx_pfalsa(vec_token* vec_tokens, token *curr_token);

// 19.
void sytx_comandos(vec_token* vec_tokens, token *curr_token);

// 20.
void sytx_cmd(vec_token* vec_tokens, token *curr_token);

// 21.
void sytx_condicao(vec_token* vec_tokens, token *curr_token);

// 22.
void sytx_relacao(vec_token* vec_tokens, token *curr_token);

// 23.
void sytx_expressao(vec_token* vec_tokens, token *curr_token);

// 24.
void sytx_op_un(vec_token* vec_tokens, token *curr_token);

// 25.
void sytx_outros_termos(vec_token* vec_tokens, token *curr_token);

// 26.
void sytx_op_ad(vec_token* vec_tokens, token *curr_token);

// 27.
void sytx_termo(vec_token* vec_tokens, token *curr_token);

// 28.
void sytx_mais_fatores(vec_token* vec_tokens, token *curr_token);

// 30.
void sytx_fator(vec_token* vec_tokens, token *curr_token);

// 31.
void sytx_numero(vec_token* vec_tokens, token *curr_token);

