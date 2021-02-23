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
#include <time.h>

#define TAMANHO_MAXIMO_DA_ENTRADA 36

// Vetor que armazena os dados vindos da Serial
char string_entrada[TAMANHO_MAXIMO_DA_ENTRADA];

// Vetor temporário que armazena o deslocamentos
char tmp[TAMANHO_MAXIMO_DA_ENTRADA] = "";

// String de copia para não afetar o original
char copia[TAMANHO_MAXIMO_DA_ENTRADA] = "";

// Struct definida para guardar as informações de índice e texto rotacionado
struct string_com_posicao {
  int posicao;
  char string_rotacionada[TAMANHO_MAXIMO_DA_ENTRADA];
};

// Vetor que armazenará cada linha rotacionada da string e suas posições originais
// Espaço alocado de 1296 chars, pois é um vetor de string, ou seja,
// Cada string contem 36 chars, e o vetor possui 36 strings.
struct string_com_posicao lista_de_strings[TAMANHO_MAXIMO_DA_ENTRADA];

// Salva as posições ordenadas da lista rotacionada
// Receberá o último elemento de cada string rotacionada da matriz
char string_rotacionada[TAMANHO_MAXIMO_DA_ENTRADA];

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
  for (i = 0; copia[i] != 0; i++) {
    new_idx = (i + qtd_posicoes) % len;
    tmp[new_idx] = copia[i];
  }
  memcpy(copia, tmp, len);
}


struct string_com_posicao* posicao_a;
struct string_com_posicao* posicao_b;

// Função de comparação para ordenar as string em ordem alfabética
// Usada pelo qsort na função rotaciona_string()
int funcao_comparacao(const void* a, const void* b) {
  posicao_a = (struct string_com_posicao*)a;
  posicao_b = (struct string_com_posicao*)b;
  return strcmp(posicao_a->string_rotacionada, posicao_b->string_rotacionada);
}

// Declaração do tamanho da entrada
int tamanho = 0;

// Realiza o ciclo de rotações da string informada
void burrows_wheeler() {
  tamanho = strlen(string_entrada);
  
  // Preence o vetor string_com_posicao com as linhas rotacionadas.
  // Gera a matriz com as rotações.
  for (j = 0; j < tamanho; j++) {
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
  for (k = 0; k < tamanho; k++) {
    string_rotacionada[k] = lista_de_strings[k].string_rotacionada[tamanho - 1];
  }
}

int main() {
    memset(string_entrada, 0, sizeof(string_entrada));
    scanf("%[^\n]", string_entrada);
    
    if (strlen(string_entrada) > TAMANHO_MAXIMO_DA_ENTRADA - 2) { // -2 por conta do '$' e do '\0'
      printf("Máximo de ");
      printf("%d",TAMANHO_MAXIMO_DA_ENTRADA + 1);
      printf(" caracteres!\n");
    } else {
      strcat(string_entrada, "$"); // Concatena '$' ao final da string, usado na etapa de verificação.
      printf("Texto a ser tranformado: ");
      printf("%s\n", string_entrada);
      printf("Método de Burrows-Wheeler: ");
	  clock_t ini = clock(); // guardas o inicial
      burrows_wheeler(); // Execução da transformação
	  printf("Funcao executou em %f microssegundos\n", ((double)clock() - ini) / CLOCKS_PER_SEC * 1000000);
      printf("%s\n", string_rotacionada);
    }
}
