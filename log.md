# Parte 2

1. Correção dos eventuais erros na análise léxica feita no Trabalho 1;
    - underline pode estar no identificador mas não pode ser o primeiro caracter

2. Implementação do analisador sintático descendente preditivo recursivo (substituindo o procedimento genérico que foi incluído no Trabalho 1);

3. Implementação do tratamento de erros sintáticos pelo modo pânico.

## Quests

    [x] Fazer o léxico printar a linha.
    [X] Função get_token para o sintatico
    [X] Arrumar os tokens com erro
    [X] Vetor de erros
    [X] Numero da linha ta errado
        - Como a gnt volta a cabeca de leitura no lookahead, ele le o /n duas vezes
    [ ] Implementar busca por seguidores
        - Previnir a avalanche de erros que atualmente assola o código

## LL(1)

    [X] Transformar o P-- em LL(1) --> tem que incluir umas regras a mais

## Estratégia ASD

    1. Chamar o ASD na main
    2. Colocar todas as funções num arquivo separado
    3. ERROS ????
        - Sepa é melhor deixar o arquivo aberto e ir colocando os erros

### Estretégia 1 (escolhida)

    - Rodar o léxico primeiro e trabalhar com os vetores que criamos no trabalho 1.
    - Colocar um novo campo no token pra indicar a linha que ele está

## Duvidas

    - Rodar o léixco primeiro e depois o sintático? (vetor de tokens)
    - Como fazer para printar os erros?
        - Não precisa mais printar o vetor de tokens (era onde ficavam os erros)
    - Como saber o numero da linha

## Mensagens de Erro

    [] Identificar se o erro é lexico ou sintático


## Mussattinho
    [X] Verificar todas as mensagens de erro (padronizar)
    [X] Verificar locais onde tem "," (comma) e ":" (colon)
    [] Testar comandos faltando o  ultimo pareneses
    
    - Modo panico so reconhece falta de argumento, se tiver coisa a mais, ele só ignora por causa do modo pânico

    -Tava colocando o caracter invalido na mensagem de erro, ta dando problema no free do vetor de tokens
