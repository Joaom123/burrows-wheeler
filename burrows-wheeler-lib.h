/*
   @(#)burrows-wheeler-lib.h

   Copyright 2019 by Anureet Kaur,
   Geeks for geeks ORG
   Free source-code.

*/
/*--------------------------------------------------------------
  --  #1.
  --  Date: Aug, 08, 2019
  --  Author: Anureet Kaur
  --  Motivo: Contribute to students
  --  Código legado: https://www.geeksforgeeks.org/burrows-wheeler-data-transform-algorithm/
  -------------------------------------------------------------
  --  #2.
  --  Date: Dec, 11, 2020
  --  Author: Elysson Gabriel e João Marcus
  --  Motivo: Trabalho da disciplina de
      Sistemas Embarcados 2020.2, Professor: Elias Teodoro
  -------------------------------------------------------------
  --  #3.
  --  Date: Jan, 7, 2021
  --  Author: Elysson Gabriel e João Marcus
  --  Motivo: Trabalho da disciplina de
      Sistemas Embarcados 2020.2, Professor: Elias Teodoro
  --  Adaptação realizada para migrar o código .c para o microcontrolador Arduino UNO
  -------------------------------------------------------------
**/
/**
  A transformada de Burrows-Wheeler constrói uma matriz n x n onde n é o tamanho do vetor que será comprimido.
  Esta matriz é preenchida na primeira linha com o vetor original; na segunda linha com o vetor rotacionado a esquerda de uma posição;
  na terceira linha com o vetor rotacionado de 2 posições, e assim por diante, até termos na última linha o vetor rotacionado de n-1 posições.
  Desta nova matriz, a última coluna pode ser facilmente comprimida por técnicas de move-to-front.

  - Modo de uso:
  A plataforma destinada a executar este código é o microcontrolador Arduino UNO, utilizando como entrada de dados a comunicação Serial e exibindo
  o resultado do processamento descrito anteriormente também pela mesma.
 **/

#include "burrows-wheeler-core.h"

int len, new_idx;
int i = 0, j = 0, k = 0;
int qtd_posicoes = 0;

// Função que desloca a string em x posições
void desloca_posicao()
{
  strcpy(copia, string_entrada);
  strcpy(tmp, copia);
  len = strlen(copia);
  if (qtd_posicoes < 0)
    qtd_posicoes = len + (qtd_posicoes % len);
  for (i = 0; copia[i] != 0; i++)
  {
    new_idx = (i + qtd_posicoes) % len;
    tmp[new_idx] = copia[i];
  }
  memcpy(copia, tmp, len);
}

// Realiza o ciclo de rotações da string informada
void burrows_wheeler()
{
  tamanho = strlen(string_entrada);

  // Preence o vetor string_com_posicao com as linhas rotacionadas.
  // Gera a matriz com as rotações.
  for (j = 0; j < tamanho; j++)
  {
    lista_de_strings[j].posicao = j;
    qtd_posicoes = -j;
    desloca_posicao();
    strcpy(lista_de_strings[j].string_rotacionada, tmp);
  }

  // Coloca os textos de string_com_posicaos em ordem alfabética.
  // Ordenação da matriz das rotações.
  qsort(lista_de_strings, tamanho, sizeof(struct string_com_posicao), funcao_comparacao);

  memset(string_rotacionada, 0, sizeof(string_rotacionada));

  // Preenche o vetor string_rotacionada com o último elemento de cada string na matriz lista_de_strings
  for (k = 0; k < tamanho; k++)
  {
    string_rotacionada[k] = lista_de_strings[k].string_rotacionada[tamanho - 1];
  }
}
