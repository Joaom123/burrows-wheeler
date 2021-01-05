/*
   @(#)burrows-wheeler.c

   Copyright 2019 by Anureet Kaur,
   Geeks for geeks ORG
   Free source-code.

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
  --  #3.
  --  Date: Jan, 5, 2021
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

// Função que desloca a string em x posições
char* desloca_posicao(char* string, int quantidade)
{
  //vetor temporário que armazena o deslocamentos
  static char tmp[35] = "";
  // string de copia para não afetar a original
  static char copia[35] = "";
  strcpy(copia, string);
  strcpy(tmp, strdup(copia));
  int len = strlen(copia);
  if (quantidade < 0)
    quantidade = len + (quantidade % len);
  for (int i = 0; copia[i] != 0; i++) {
    int new_idx = (i + quantidade) % len;
    tmp[new_idx] = copia[i];
  }
  memcpy(copia, tmp, len);
  return tmp;
}

// Struct definida para guardar as informações de índice e texto rotacionado
struct string_com_posicao {
  int posicao;
  char string_rotacionada[35];
};

// Função de comparação para ordenar as string em ordem alfabética
// Usada pelo qsort na função rotaciona_string()
int funcao_comparacao(const void* a, const void* b) {
  struct string_com_posicao* posicao_a = (struct string_com_posicao*)a;
  struct string_com_posicao* posicao_b = (struct string_com_posicao*)b;
  return strcmp(posicao_a->string_rotacionada, posicao_b->string_rotacionada);
}

// Realiza o ciclo de rotações da string informada
char* transforma_string(char* string_entrada, int tamanho) {
  // Vetor que armazenará cada linha rotacionada da string e suas posições originais
  // Espaço alocado de 2025 chars, pois é um vetor de string, ou seja,
  // Cada string contem 45 chars, e o vetor possui 45 strings.
  struct string_com_posicao lista_de_strings[35];

  // Preence o vetor string_com_posicao com as linhas rotacionadas
  for (int i = 0; i < tamanho; i++) {
    lista_de_strings[i].posicao = i;
    strcpy(lista_de_strings[i].string_rotacionada, desloca_posicao(string_entrada, -i));
  }

  // Coloca os textos de string_com_posicaos em ordem alfabética
  qsort(lista_de_strings, tamanho, sizeof(struct string_com_posicao), funcao_comparacao);

  // Salva as posições ordenadas da lista rotacionada
  static char string_rotacionada[35];
  for (int i = 0; i < tamanho; i++) {
    string_rotacionada[i] = lista_de_strings[i].string_rotacionada[tamanho - 1];
  }

  return string_rotacionada;
}

// Método de Burrows - Wheeler
char* burrows_wheeler(char* string_entrada) {
  int tamanho = strlen(string_entrada);

  // Realiza as rotações da string original
  char* transformada_burrows_wheeler = transforma_string(string_entrada, tamanho);

  return transformada_burrows_wheeler;
}

char entrada[35];
char* saida;
const char *entradaPonteiro;
unsigned long tempoAntesDaTransformada;
unsigned long tempoDepoisDaTransformada;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String entradaDaSerial = Serial.readString();
    entradaPonteiro = entradaDaSerial.c_str(); //Transforma String para ponteiro em C

    Serial.print("Texto a ser transformado: ");
    Serial.println(entradaPonteiro);

    strcpy(entrada, entradaPonteiro); // transforma char * para char []
    strcat(entrada, "$"); // adiciona $ ao final da string entrada

    tempoAntesDaTransformada = millis();
    saida = burrows_wheeler(entrada);
    tempoDepoisDaTransformada = millis();

    Serial.print("Método de Burrows-Wheeler: ");
    Serial.println(saida);

    Serial.print("O tempo gasto pela transformada foi: ");
    Serial.print(tempoDepoisDaTransformada - tempoAntesDaTransformada);
    Serial.println(" ms");

    //TODO: Imprimir o tempo gasto pela transformada
  }

}
