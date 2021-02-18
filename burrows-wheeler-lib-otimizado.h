/*
 * @(#)burrows-wheeler-lib-otimizado.h
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
#include "burrows-wheeler-core.h"

// Struct definida para guardar as informações do índice (posição) e texto rotacionado (string_rotacionada)
// struct string_com_posicao {
//     int posicao;
//     char* string_rotacionada;
// };

// Realiza o ciclo de rotações da string informada
int *rotaciona_string(char *string_entrada)
{
  // Preence o vetor string_com_posicao com as linhas rotacionadas
  for (int i = 0; i < tamanho; i++)
  {
    lista_de_strings[i].posicao = i;
    strcpy(lista_de_strings[i].string_rotacionada, (string_entrada + i));
  }

  // Coloca os textos de string_com_posicaos em ordem alfabética
  qsort(lista_de_strings, tamanho, sizeof(struct string_com_posicao), funcao_comparacao);

  // Salva as posições ordenadas da lista rotacionada
  int *string_rotacionada_a = (int *)malloc(tamanho*sizeof(int));

  for (int i = 0; i < tamanho; i++)
  {
    string_rotacionada_a[i] = lista_de_strings[i].posicao;
  }

  // Marca o final da string
  string_rotacionada_a[tamanho] = '\0';

  return string_rotacionada_a;
}

// Método de Burrows - Wheeler
void burrows_wheeler()
{
  // Guarda o tamanho da entrada
  tamanho = strlen(string_entrada);

  // Realiza as rotações da string original
  int *string_rotacionada_a = rotaciona_string(string_entrada);

  // Vetor a ser preenchido com a última coluna da rotação
  char *transformada_burrows_wheeler = (char *)malloc(tamanho * sizeof(char));

  // Preenche o vetor anterior com o último caractere de cada rotação
  for (int i = 0; i < tamanho; i++)
  {
    int j = string_rotacionada_a[i] - 1;
    if (j < 0)
    {
      j = j + tamanho;
    }
    transformada_burrows_wheeler[i] = string_entrada[j];
  }

  // Marca o final da string
  transformada_burrows_wheeler[tamanho] = '\0';

  strcpy(string_rotacionada, transformada_burrows_wheeler);
}