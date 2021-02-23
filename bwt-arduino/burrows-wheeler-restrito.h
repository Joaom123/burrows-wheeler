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

// Constante que estabelece o tamanho da string de entrada
#define TAMANHO_MAXIMO_DA_ENTRADA 36

// Vetor que armazena os dados vindos da Serial
char string_entrada[TAMANHO_MAXIMO_DA_ENTRADA];

// Vetor temporário que armazena o deslocamentos
char tmp[TAMANHO_MAXIMO_DA_ENTRADA] = "";

// String de copia para não afetar o original
char copia[TAMANHO_MAXIMO_DA_ENTRADA] = "";

// Salva as posições ordenadas da lista rotacionada
// Receberá o último elemento de cada string rotacionada da matriz
char string_rotacionada[TAMANHO_MAXIMO_DA_ENTRADA];

// Declaração do tamanho da entrada
int tamanho_da_entrada = 0;

int len, new_idx;
int i = 0, j = 0, k = 0;
int qtd_posicoes = 0;

// Struct definida para guardar as informações de índice e texto rotacionado
struct string_com_posicao
{
  int posicao;
  char string_rotacionada[TAMANHO_MAXIMO_DA_ENTRADA];
};

struct string_com_posicao *posicao_a;
struct string_com_posicao *posicao_b;

// Função de comparação para ordenar as string em ordem alfabética
// Usada pelo qsort na função rotaciona_string()
int funcao_comparacao(const void *a, const void *b)
{
  posicao_a = (struct string_com_posicao *)a;
  posicao_b = (struct string_com_posicao *)b;
  return strcmp(posicao_a->string_rotacionada, posicao_b->string_rotacionada);
}

// Vetor que armazenará cada linha rotacionada da string e suas posições originais
// Espaço alocado de 1296 chars, pois é um vetor de string, ou seja,
// Cada string contem 36 chars, e o vetor possui 36 strings.
struct string_com_posicao lista_de_strings[TAMANHO_MAXIMO_DA_ENTRADA];

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
  tamanho_da_entrada = strlen(string_entrada);

  // Preence o vetor string_com_posicao com as linhas rotacionadas.
  // Gera a matriz com as rotações.
  for (j = 0; j < tamanho_da_entrada; j++)
  {
    lista_de_strings[j].posicao = j;
    qtd_posicoes = -j;
    desloca_posicao();
    strcpy(lista_de_strings[j].string_rotacionada, tmp);
  }

  // Coloca os textos de string_com_posicaos em ordem alfabética.
  // Ordenação da matriz das rotações.
  qsort(lista_de_strings, tamanho_da_entrada, sizeof(struct string_com_posicao), funcao_comparacao);

  memset(string_rotacionada, 0, sizeof(string_rotacionada));

  // Preenche o vetor string_rotacionada com o último elemento de cada string na matriz lista_de_strings
  for (k = 0; k < tamanho_da_entrada; k++)
  {
    string_rotacionada[k] = lista_de_strings[k].string_rotacionada[tamanho_da_entrada - 1];
  }
}
