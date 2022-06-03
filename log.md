
# O que falta fazer

    - [ ] Preencher a matriz de transição de estados 
    - [ ] Terminar de codar os erros
    - [ ] Vetor de tokens
    - [ ] Resolver problema do símbolo mais
    - [ ] Função get_token
    - [ ] Plavras Reservadas
    - [ ] Organizar melhor o código
        - Rever ordem das funções no .h
    - [ ] Comentar o código
    - [ ] Testar  

# Funcões Não Implementadas

## file.h

    - [ ] check_EOF()
    - [ ] FILE* create_new_file(char* name);
    - [ ] void write_tokens_file(FILE *fp, vec_token vec_tokens);   
        - Não printar o ultimo toke (EOF)

## token.h
    - [ ] create_tokens_vector
    - [ ] last_vec_token(vec_token* vec_tokens)
    - [ ] vec_tokens_push_back
    - [ ] free_tokens_vector(vec_token* vec_tokens);

# Estratégia para o símbolo mais

    - Mandar o vetor de tokens para a função get_token()
    - Verificar se o ultimo foi um numero 
        - Se sim --> soma --> retornar apenas o mais
        - Se não --> Numero inteiro --> continuar lendo o numero
    - Adicionar uma condição no while para verificar se está no estado do mais e se o ultimo lido foi um número