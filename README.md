# Análise de Algoritmos de Casamento de Strings

Este projeto é um analisador de desempenho para algoritmos de casamento de strings, implementando três algoritmos diferentes: **KMP**, **Força Bruta** e **Shift-And**. O código é projetado para comparar o tempo de execução dos algoritmos, tanto em execução sequencial quanto paralela usando threads.

## Índice

- [Descrição](#descrição)
- [Compilação](#compilação)
- [Uso](#uso)
- [Configuração](#configuração)
- [Medição de Tempo](#medição-de-tempo)

## Descrição

O código realiza a análise de desempenho de três algoritmos de casamento de strings:
- **KMP** (Knuth-Morris-Pratt)
- **Força Bruta**
- **Shift-And**

O programa pode ser executado em modo sequencial ou paralelo, dependendo das configurações definidas em um arquivo de variáveis de ambiente.

## Compilação

Para compilar o código, certifique-se de que você possui um compilador C e as bibliotecas necessárias. Utilize o seguinte comando para compilar:

```bash
make
```

## Uso

Execute o programa fornecendo o arquivo de entrada como argumento. O arquivo deve estar no formato apropriado para os algoritmos de casamento de strings.

```bash
./tp3 <Arquivo de entrada>
```

## Configuração

As configurações para o modo de execução e algoritmos a serem usados são definidas em um arquivo de variáveis de ambiente chamado `variaveis_ambiente.env`. Aqui está um exemplo de como o arquivo pode ser configurado:

```
EXECUCAO_PARALELA=true
ALGORITMO_PRINCIPAL=kmp
SHIFT_AND=true
KMP=true
FORCA_BRUTA=true
```

## Medição de Tempo

O programa mede o tempo de execução dos algoritmos de três maneiras:
- **Tempo Sistema**: Tempo de CPU usado pelo sistema.
- **Tempo Usuário**: Tempo de CPU usado pela aplicação.
- **Tempo Total**: Tempo real total decorrido.

No modo paralelo, o tempo de execução de cada thread é medido individualmente e apresentado separadamente.

## Exemplo de Saída

Aqui está um exemplo da saída do programa:

```
----------------------------------------------
Shift and :
        Tempo sistema : 0.000000
        Tempo usuario : 0.003276
        Tempo total   : 0.001199
----------------------------------------------
Kmp :
        Tempo sistema : 0.000000
        Tempo usuario : 0.001121
        Tempo total   : 0.000897
----------------------------------------------
Força bruta :
        Tempo sistema : 0.000000
        Tempo usuario : 0.002103
        Tempo total   : 0.001134
----------------------------------------------
```
