/*
 * @(#)burrows-wheeler.ino
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

//constante que estabelece o tamanho da string de entrada
#define TAMANHO_MAXIMO_DA_ENTRADA 36

//configurando para 9600 o baud rate da Serial do Arduino
void setup() {
  Serial.begin(9600);
}

// vetor que armazena os dados vindos da Serial
char string_entrada[TAMANHO_MAXIMO_DA_ENTRADA];

// vetor temporário que armazena o deslocamentos
char tmp[TAMANHO_MAXIMO_DA_ENTRADA] = "";

// string de copia para não afetar a original
char copia[TAMANHO_MAXIMO_DA_ENTRADA] = "";

// Struct definida para guardar as informações de índice e texto rotacionado
struct string_com_posicao {
    int posicao;
    char string_rotacionada[TAMANHO_MAXIMO_DA_ENTRADA];
};

// Vetor que armazenará cada linha rotacionada da string e suas posições originais
// Espaço alocado de 1369 chars, pois é um vetor de string, ou seja,
// Cada string contem 37 chars, e o vetor possui 37 strings.
struct string_com_posicao lista_de_strings[TAMANHO_MAXIMO_DA_ENTRADA];

// Salva as posições ordenadas da lista rotacionada
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

// Função de comparação para ordenar as string em ordem alfabética
// Usada pelo qsort na função rotaciona_string()
struct string_com_posicao* posicao_a;
struct string_com_posicao* posicao_b;

int funcao_comparacao(const void* a, const void* b) {
    posicao_a = (struct string_com_posicao*)a;
    posicao_b = (struct string_com_posicao*)b;
    return strcmp(posicao_a->string_rotacionada, posicao_b->string_rotacionada);
}

// Realiza o ciclo de rotações da string informada
int tamanho = 0;
void burrows_wheeler() {
    // Preence o vetor string_com_posicao com as linhas rotacionadas
    tamanho = strlen(string_entrada);
    for (j = 0; j < tamanho; j++) {
        lista_de_strings[j].posicao = j;
        qtd_posicoes = -j;
        desloca_posicao();
        strcpy(lista_de_strings[j].string_rotacionada, tmp);
    }
    
    // Coloca os textos de string_com_posicaos em ordem alfabética
    qsort(lista_de_strings, tamanho, sizeof(struct string_com_posicao), funcao_comparacao);
    
    memset(string_rotacionada, 0, sizeof(string_rotacionada));
    for (k = 0; k < tamanho; k++) {
        string_rotacionada[k] = lista_de_strings[k].string_rotacionada[tamanho-1];
    }
}

void loop() {
  if(Serial.available() > 0){
    memset(string_entrada, 0, sizeof(string_entrada));
    (Serial.readBytesUntil('\n', string_entrada, TAMANHO_MAXIMO_DA_ENTRADA));//.toCharArray(string_entrada, TAMANHO_MAXIMO_DA_ENTRADA + 1);
    // -2 Por conta do $ e do \0
    if(strlen(string_entrada) > TAMANHO_MAXIMO_DA_ENTRADA - 2){
      Serial.print("Máximo de ");
      Serial.print(TAMANHO_MAXIMO_DA_ENTRADA);
      Serial.println(" caracteres!");
    }else{
      strcat(string_entrada, "$");
      Serial.print("Texto a ser tranformado: ");
      Serial.println(string_entrada);
      Serial.print("Método de Burrows-Wheeler: ");
      burrows_wheeler();
      Serial.println(string_rotacionada);
    }
  }
}
