// Struct definida para guardar as informações do índice (posição) e texto rotacionado (string_rotacionada)
struct string_com_posicao {
  int posicao;
  char* string_rotacionada;
};

// Função de comparação para ordenar as string em ordem alfabética
// Usada pelo qsort na função rotaciona_string()
int funcao_comparacao(const void* a, const void* b) {
  struct string_com_posicao* posicao_a = (struct string_com_posicao*)a;
  struct string_com_posicao* posicao_b = (struct string_com_posicao*)b;
  return strcmp(posicao_a->string_rotacionada, posicao_b->string_rotacionada);
}

// Realiza o ciclo de rotações da string informada
int* rotaciona_string(char* string_entrada, int tamanho_da_entrada) {
  // Vetor que armazenará cada linha rotacionada da string e suas posições originais
  struct string_com_posicao lista_de_strings[tamanho_da_entrada];

  // Preence o vetor string_com_posicao com as linhas rotacionadas
  for (int i = 0; i < tamanho_da_entrada; i++) {
    lista_de_strings[i].posicao = i;
    lista_de_strings[i].string_rotacionada = (string_entrada + i);
  }

  // Coloca os textos de string_com_posicao em ordem alfabética
  qsort(lista_de_strings, tamanho_da_entrada, sizeof(struct string_com_posicao), funcao_comparacao);

  // Salva as posições ordenadas da lista rotacionada
   int *string_rotacionada = (int *)malloc(tamanho_da_entrada*sizeof(int));
//  static int string_rotacionada[tamanho_da_entrada];

  for (int i = 0; i < tamanho_da_entrada; i++) {
    string_rotacionada[i] = lista_de_strings[i].posicao;
  }

  // Marca o final da string
  string_rotacionada[tamanho_da_entrada] = '\0';

  return string_rotacionada;
}

// Método de Burrows - Wheeler
char* burrows_wheeler(char* string_entrada) {
  // Guarda o tamanho da entrada
  int tamanho_da_entrada = strlen(string_entrada);

  // Realiza as rotações da string original
  int* string_rotacionada = rotaciona_string(string_entrada, tamanho_da_entrada);

  // Vetor a ser preenchido com a última coluna da rotação
   char *transformada_burrows_wheeler = (char *)malloc(tamanho_da_entrada*sizeof(char));
//  static char transformada_burrows_wheeler[tamanho_da_entrada];

  // Preenche o vetor anterior com o último caractere de cada rotação
  for (int i = 0; i < tamanho_da_entrada; i++) {
    int j = string_rotacionada[i] - 1;
    if (j < 0) {
      j = j + tamanho_da_entrada;
    }
    transformada_burrows_wheeler[i] = string_entrada[j];
  }

  // Marca o final da string
  transformada_burrows_wheeler[tamanho_da_entrada] = '\0';

  // Retorna o resultado da transformada de Burrows-Wheeler
  return transformada_burrows_wheeler;
}
