/*
 * @(#)burrows-wheeler-core.h
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

// Constante que estabelece o tamanho da string de entrada
#define TAMANHO_MAXIMO_DA_ENTRADA 36

// Vetor que armazena os dados vindos da Serial
char string_entrada[TAMANHO_MAXIMO_DA_ENTRADA];

// Vetor temporário que armazena o deslocamentos
char tmp[TAMANHO_MAXIMO_DA_ENTRADA] = "";

// String de copia para não afetar o original
char copia[TAMANHO_MAXIMO_DA_ENTRADA] = "";

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

// Declaração do tamanho da entrada
int tamanho_da_entrada = 0;

// Vetor que armazenará cada linha rotacionada da string e suas posições originais
// Espaço alocado de 1296 chars, pois é um vetor de string, ou seja,
// Cada string contem 36 chars, e o vetor possui 36 strings.
struct string_com_posicao lista_de_strings[TAMANHO_MAXIMO_DA_ENTRADA];

// Salva as posições ordenadas da lista rotacionada
// Receberá o último elemento de cada string rotacionada da matriz
char string_rotacionada[TAMANHO_MAXIMO_DA_ENTRADA];
