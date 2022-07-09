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


token* get_token_from_vector(vec_token* vec_tokens, token *curr_token);

int ASD(vec_token* vec_tokens);

void sytx_programa(vec_token* vec_tokens, token *curr_token);

void sytx_corpo(vec_token* vec_tokens, token *curr_token);

sytx_dc(vec_token* vec_tokens, token *curr_token);    