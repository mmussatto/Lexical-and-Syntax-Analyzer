
# O que falta fazer

    - [ ] Preencher a matriz de transição de estados 
    - [ X ] Terminar de codar os erros
        - [ X ] Transformar para token
        - [ X ] Preencher o type do error token
    - [ ] Vetor de tokens
    - [ X ] Resolver problema do símbolo mais
    - [ X ] Função get_token
    - [  ] Plavras Reservadas
    - [  ] Organizar melhor o código
        - Rever ordem das funções no .h
    - [  ] Comentar o código
    - [  ] Testar  

# Funcões Não Implementadas

## file.h

    - [X] check_EOF() //Checar para ver se era isso mesmo
    - [X] FILE* create_new_file(char* name); //Não é necessário, basta abrir um novo arquivo no modo a
    - [X] void write_tokens_file(FILE *fp, vec_token vec_tokens); //Feito, verificar se é isso mesmo   
        - [  ] Não printar o ultimo toke (EOF)/
        - [  ] Não printar token com type comment

## token.h
    - [X] create_tokens_vector
    - [X] last_vec_token(vec_token* vec_tokens)
    - [X] vec_tokens_push_back
    - [X] free_tokens_vector(vec_token* vec_tokens);

# Estratégia para o símbolo mais

    - Mandar o vetor de tokens para a função get_token()
    - Verificar se o ultimo foi um numero 
        - Se sim --> soma --> retornar apenas o mais
        - Se não --> Numero inteiro --> continuar lendo o numero
    - Adicionar uma condição no while para verificar se está no estado do mais e se o ultimo lido foi um número