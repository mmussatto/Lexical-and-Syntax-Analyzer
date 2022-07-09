# Parte 2

1. Correção dos eventuais erros na análise léxica feita no Trabalho 1;
    - underline pode estar no identificador mas não pode ser o primeiro caracter

2. Implementação do analisador sintático descendente preditivo recursivo (substituindo o procedimento genérico que foi incluído no Trabalho 1);

3. Implementação do tratamento de erros sintáticos pelo modo pânico.

## Quests

    [x] Fazer o léxico printar a linha.
    [X] Função get_token para o sintatico
    [ ] Arrumar os tokens com erro
    [ ] Vetor de erros
    [ ] Nunmero da linha ta errado
        - Como a gnt volta a cabeca de leitura no lookahead, ele le o /n duas vezes

## LL(1)

    Transformar o P-- em LL(1) --> tem que incluir umas regras a mais

## Estratégia ASD

    1. Chamar o ASD na main
    2. Colocar todas as funções num arquivo separado
    3. ERROS ????
        - Sepa é melhor deixar o arquivo aberto e ir colocando os erros

### Estretégia 1 (escolhida)

    - Rodar o léxico primeiro e trabalhar com os vetores que criamos no trabalho 1.
    - Colocar um novo campo no token pra indicar a linha que ele está

### Estratégia 2

    - Modificar o léxico para rodar junto com o 
    -


## Duvidas

    - Rodar o léixco primeiro e depois o sintático? (vetor de tokens)
    - Como fazer para printar os erros?
        - Não precisa mais printar o vetor de tokens (era onde ficavam os erros)
    - Como saber o numero da linha

## Mensagens de Erro

    [ ] Identificar se o erro é lexico ou sintático

    
