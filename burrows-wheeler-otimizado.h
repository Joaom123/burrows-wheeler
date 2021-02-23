/*
 * @(#)burrows-wheeler.c
 *
 * Copyright 2019 by Anureet Kaur,
 * Geeks for geeks ORG
 * Free source-code.
 *
 */
/*--------------------------------------------------------------
--  #1.
--  Date: Aug, 08, 2019
--  Author: Anureet Kaur
--  Motivo: Contribute to students
-------------------------------------------------------------
--  #2.
--  Date: Dec, 11, 2020
--  Author: Elysson Gabriel e João Marcus
--  Motivo: Trabalho da disciplina de 
			Sistemas Embarcados 2020.2, Professor: Elias Teodoro
-------------------------------------------------------------
**/
/**
A transformada de Burrows-Wheeler constrói uma matriz n x n onde n é o tamanho do vetor que será comprimido.
Esta matriz é preenchida na primeira linha com o vetor original; na segunda linha com o vetor rotacionado a esquerda de uma posição;
na terceira linha com o vetor rotacionado de 2 posições, e assim por diante, até termos na última linha o vetor rotacionado de n-1 posições.
Desta nova matriz, a última coluna pode ser facilmente comprimida por técnicas de move-to-front.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constante que estabelece o tamanho da string de entrada
#define TAMANHO_MAXIMO_DA_ENTRADA 36

// Vetor que armazena os dados vindos da Serial
char string_entrada[TAMANHO_MAXIMO_DA_ENTRADA];

// Salva as posições ordenadas da lista rotacionada
// Receberá o último elemento de cada string rotacionada da matriz
char string_rotacionada[TAMANHO_MAXIMO_DA_ENTRADA];

// Struct definida para guardar as informações do índice (posição) e texto rotacionado (string_rotacionada)
struct string_com_posicao
{
    int posicao;
    char *string_rotacionada;
};

// Função de comparação para ordenar as string em ordem alfabética
// Usada pelo qsort na função rotaciona_string()
int funcao_comparacao(const void *a, const void *b)
{
    struct string_com_posicao *posicao_a = (struct string_com_posicao *)a;
    struct string_com_posicao *posicao_b = (struct string_com_posicao *)b;
    return strcmp(posicao_a->string_rotacionada, posicao_b->string_rotacionada);
}

// Realiza o ciclo de rotações da string informada
int *rotaciona_string(char *string_entrada, int tamanho_da_entrada)
{
    // Vetor que armazenará cada linha rotacionada da string e suas posições originais
    struct string_com_posicao lista_de_strings[tamanho_da_entrada];

    // Preence o vetor string_com_posicao com as linhas rotacionadas
    for (int i = 0; i < tamanho_da_entrada; i++)
    {
        lista_de_strings[i].posicao = i;
        lista_de_strings[i].string_rotacionada = (string_entrada + i);
    }

    // Coloca os textos de string_com_posicaos em ordem alfabética
    qsort(lista_de_strings, tamanho_da_entrada, sizeof(struct string_com_posicao), funcao_comparacao);

    // Salva as posições ordenadas da lista rotacionada
    // int *string_rotacionada = (int *)malloc(tamanho_da_entrada*sizeof(int));
    static int string_rotacionada[1000];

    for (int i = 0; i < tamanho_da_entrada; i++)
    {
        string_rotacionada[i] = lista_de_strings[i].posicao;
    }

    // Marca o final da string
    string_rotacionada[tamanho_da_entrada] = '\0';

    return string_rotacionada;
}

// Método de Burrows - Wheeler
char *burrows_wheeler()
{
    // Guarda o tamanho da entrada
    int tamanho_da_entrada = strlen(string_entrada);

    // Realiza as rotações da string original
    int *string_rotacionada_a = rotaciona_string(string_entrada, tamanho_da_entrada);

    // Vetor a ser preenchido com a última coluna da rotação
    // char *transformada_burrows_wheeler = (char *)malloc(tamanho_da_entrada*sizeof(char));
    static char transformada_burrows_wheeler[1000];

    // Preenche o vetor anterior com o último caractere de cada rotação
    for (int i = 0; i < tamanho_da_entrada; i++)
    {
        int j = string_rotacionada_a[i] - 1;
        if (j < 0)
        {
            j = j + tamanho_da_entrada;
        }
        transformada_burrows_wheeler[i] = string_entrada[j];
    }

    // Marca o final da string
    transformada_burrows_wheeler[tamanho_da_entrada] = '\0';

    // Retorna o resultado da transformada de Burrows-Wheeler
    strcpy(string_rotacionada, transformada_burrows_wheeler);
}
