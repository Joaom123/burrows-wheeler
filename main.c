#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
  
// Structure to store data of a string_com_posicao 
struct string_com_posicao { 
    int posicao; 
    char* string_rotacionada; 
}; 
  
// Compares the string_com_posicaos and 
// sorts the string_com_posicaos alphabetically 
int funcao_comparacao(const void* a, const void* b) { 
    struct string_com_posicao* posicao_a = (struct string_com_posicao*)a; 
    struct string_com_posicao* posicao_b = (struct string_com_posicao*)b; 
    return strcmp(posicao_a->string_rotacionada, posicao_b->string_rotacionada); 
} 
  
// Takes text to be transformed and its length as 
// arguments and returns the corresponding string_rotacionada array 
int* rotaciona_string(char* string_entrada, int tamanho) { 
    // Array of structures to store string_com_posicaos and 
    // their posicaoes 
    struct string_com_posicao lista_de_strings[tamanho]; 
  
    // Structure is needed to maintain old posicaoes of 
    // string_com_posicaos after sorting them 
    for (int i = 0; i < tamanho; i++) { 
        lista_de_strings[i].posicao = i; 
        lista_de_strings[i].string_rotacionada = (string_entrada + i); 
    } 
  
    // Sorts string_com_posicaos using comparison 
    // function defined above 
    qsort(lista_de_strings, tamanho, sizeof(struct string_com_posicao), 
          funcao_comparacao); 
  
    // Stores the posicaoes of sorted string_com_posicaos 
    int* string_rotacionada 
        = (int*)malloc(tamanho * sizeof(int)); 
    for (int i = 0; i < tamanho; i++) 
        string_rotacionada[i] = lista_de_strings[i].posicao; 
  
    // Returns the computed string_rotacionada array 
    return string_rotacionada; 
} 
  
// Takes string_rotacionada array and its size 
// as arguments and returns the 
// Burrows - Wheeler Transform of given text 
void burrows_wheeler(char* string_entrada, int* string_rotacionada, int tamanho) { 
    // Iterates over the string_rotacionada array to find 
    // the last char of each cyclic string_com_posicao 
    //char* transformada_burrows_wheeler = (char*)malloc(tamanho * sizeof(char));
    char transformada_burrows_wheeler[40];
    int i; 
    for (i = 0; i < tamanho; i++) { 
        // Computes the last char which is given by 
        // string_entrada[(string_rotacionada[i] + n - 1) % n] 
        int j = string_rotacionada[i] - 1; 
        if (j < 0) 
            j = j + tamanho; 
  
        transformada_burrows_wheeler[i] = string_entrada[j]; 
    } 
  
    transformada_burrows_wheeler[i] = '\0'; 
    printf("Método de Burrows-Wheeler: %s\n", transformada_burrows_wheeler);
    // Returns the computed Burrows - Wheeler Transform  
} 
  
// Driver program to test functions above 
int main() {
    char string_entrada[] = "banana";
    strcat(string_entrada, "$");

    printf("Texto a ser tranformado: %s\n", string_entrada);

    int tamanho = strlen(string_entrada); 
    // Computes the string_rotacionada array of our text 
    int* string_rotacionada = rotaciona_string(string_entrada, tamanho); 
    // Adds to the output array the last char 
    // of each string_com_posicao 
    burrows_wheeler(string_entrada, string_rotacionada, tamanho);  
} 