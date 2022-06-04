
# O que falta fazer

    - [ X ] Preencher a matriz de transição de estados 
        - [ X ] Revisar depois de mudar automatos
    - [ X ] Terminar de codar os erros
        - [ X ] Transformar para token
        - [ X ] Preencher o type do error token
    - [ X ] Vetor de tokens
        - [ X ] Testar
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
        - [ X ] Não printar o ultimo toke (EOF)/ - decidimos printar
        - [ X ] Não printar token com type comment - decidimos printar

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

# Estrategia para erros
    - [X] Erro '-5' chegou no estado final (teoricamente nao le nada)
    - [X] Erro EOF nao existe na matriz (dar um jeitinho)

## Chezao things

    - [X] Automato para '(' e ')'   ,colocar em automato separado, continuando a numeracao de estado existente (25 e 26)
    - [X] Automato para ',' e '.', agora fudeu de vez - virgula 27 & ponto - 28
    - [X] Automato para '=' - 29
    - [X] Retirar o '_' (underline) do automato - caracter invalido
    - [X] Corrigir automato 4 (ta invertido)

    - Automato numero real, vai para estado final quando ler:
        \t, \n, espaco, *, + , ',', -, /, ;, <, >, = , {
    - Tambem occore com numero normal
        - [ ] seta do q5 para e2
        - [ ] seta do q8 pro e3
    
