#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

// ---------------------------------------------------------------
// Teste 01 - usando código da branch 'main'
// É mais seguro usar: 80 caracteres

//// Struct definida para guardar as informações do índice (posição) e texto rotacionado (string_rotacionada)
//struct string_com_posicao {
//  int posicao;
//  char* string_rotacionada;
//};
//
//// Função de comparação para ordenar as string em ordem alfabética
//// Usada pelo qsort na função rotaciona_string()
//int funcao_comparacao(const void* a, const void* b) {
//  struct string_com_posicao* posicao_a = (struct string_com_posicao*)a;
//  struct string_com_posicao* posicao_b = (struct string_com_posicao*)b;
//  return strcmp(posicao_a->string_rotacionada, posicao_b->string_rotacionada);
//}
//
//// Realiza o ciclo de rotações da string informada
//int* rotaciona_string(char* string_entrada, int tamanho_da_entrada) {
//  // Vetor que armazenará cada linha rotacionada da string e suas posições originais
//  struct string_com_posicao lista_de_strings[tamanho_da_entrada];
//
//  // Preence o vetor string_com_posicao com as linhas rotacionadas
//  for (int i = 0; i < tamanho_da_entrada; i++) {
//    lista_de_strings[i].posicao = i;
//    lista_de_strings[i].string_rotacionada = (string_entrada + i);
//  }
//
//  // Coloca os textos de string_com_posicao em ordem alfabética
//  qsort(lista_de_strings, tamanho_da_entrada, sizeof(struct string_com_posicao), funcao_comparacao);
//
//  // Salva as posições ordenadas da lista rotacionada
//  int *string_rotacionada = (int *)malloc(tamanho_da_entrada * sizeof(int));
//  //    static int string_rotacionada[50];
//
//  for (int i = 0; i < tamanho_da_entrada; i++) {
//    string_rotacionada[i] = lista_de_strings[i].posicao;
//  }
//
//  // Marca o final da string
//  string_rotacionada[tamanho_da_entrada] = '\0';
//
//  return string_rotacionada;
//}
//
//// Método de Burrows - Wheeler
//char* burrows_wheeler(char* string_entrada) {
//  // Guarda o tamanho da entrada
//  int tamanho_da_entrada = strlen(string_entrada);
//
//  // Realiza as rotações da string original
//  int* string_rotacionada = rotaciona_string(string_entrada, tamanho_da_entrada);
//
//  // Vetor a ser preenchido com a última coluna da rotação
//  char *transformada_burrows_wheeler = (char *)malloc(tamanho_da_entrada * sizeof(char));
//  //  static char transformada_burrows_wheeler[50];
//
//  // Preenche o vetor anterior com o último caractere de cada rotação
//  for (int i = 0; i < tamanho_da_entrada; i++) {
//    int j = string_rotacionada[i] - 1;
//    if (j < 0) {
//      j = j + tamanho_da_entrada;
//    }
//    transformada_burrows_wheeler[i] = string_entrada[j];
//  }
//
//  // Marca o final da string
//  transformada_burrows_wheeler[tamanho_da_entrada] = '\0';
//
//  // Retorna o resultado da transformada de Burrows-Wheeler
//  return transformada_burrows_wheeler;
//}

// ----------------------------------------------------------------------------------------------------------------
// Teste 02 - usando código da branch 'codigo_cust'
// É seguro usar:  caracteres
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que desloca a string em x posições
char* desloca_posicao(char* string, int quantidade)
{
    //vetor temporário que armazena o deslocamentos
    static char tmp[20] = "";
    // string de copia para não afetar a original
    static char copia[20] = "";
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
    char string_rotacionada[20];
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
    struct string_com_posicao lista_de_strings[20];

    // Preence o vetor string_com_posicao com as linhas rotacionadas
    for (int i = 0; i < tamanho; i++) {
        lista_de_strings[i].posicao = i;
        strcpy(lista_de_strings[i].string_rotacionada, desloca_posicao(string_entrada, -i));
    }

    // Coloca os textos de string_com_posicaos em ordem alfabética
    qsort(lista_de_strings, tamanho, sizeof(struct string_com_posicao), funcao_comparacao);

    // Salva as posições ordenadas da lista rotacionada
    static char string_rotacionada[20];
    for (int i = 0; i < tamanho; i++) {
        string_rotacionada[i] = lista_de_strings[i].string_rotacionada[tamanho-1];
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
