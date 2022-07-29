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

#include "Headers/sync.h"

// typedef struct{
//     int size;
//     int curr_size;
//     char **list_tokens;  
// }sync_stack;

stack* create_sync_stack()
{
    int tam = 100;

    stack* sync_stack = (stack*) malloc(sizeof(stack));
    sync_stack->list_tokens = (char**) malloc (tam* sizeof(char*));

    sync_stack->curr_size = 0;
    sync_stack->size = tam;

    int i;

    for (i = 0; i < sync_stack->size; i++)
        sync_stack->list_tokens[i] = NULL;

    return sync_stack;
}


void free_sync_stack(stack* sync_stack)
{
    int i;

    for (i = 0; i < sync_stack->size; i++){
        if (sync_stack->list_tokens[i] != NULL)
            free(sync_stack->list_tokens[i]);
    }

    free(sync_stack);
}

void sync_push (stack* sync_stack, char* string)
{

    sync_stack->list_tokens[sync_stack->curr_size] = strdup(string);
    sync_stack->curr_size++;

}

void sync_pop (stack* sync_stack, int n)
{
    while (n-- && sync_stack->curr_size > 0)
        sync_stack->curr_size--;
    
}


