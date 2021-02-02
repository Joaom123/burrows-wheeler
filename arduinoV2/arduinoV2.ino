void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

String recebi;
char string_entrada[35];

//vetor temporário que armazena o deslocamentos
static char tmp[35] = "";
// string de copia para não afetar a original
static char copia[35] = "";

// Struct definida para guardar as informações de índice e texto rotacionado
struct string_com_posicao {
    int posicao;
    char string_rotacionada[35];
};

// Vetor que armazenará cada linha rotacionada da string e suas posições originais
// Espaço alocado de 3525 chars, pois é um vetor de string, ou seja,
// Cada string contem 45 chars, e o vetor possui 45 strings.
struct string_com_posicao lista_de_strings[35];

// Salva as posições ordenadas da lista rotacionada
static char string_rotacionada[35];

int len, new_idx;
int i = 0, j = 0, k = 0;

char* desloca_posicao(char* string, int quantidade)
{
    strcpy(copia, string);
    strcpy(tmp, strdup(copia));
    len = strlen(copia);
    if (quantidade < 0)
        quantidade = len + (quantidade % len);
    for (i = 0; copia[i] != 0; i++) {
        new_idx = (i + quantidade) % len;
        tmp[new_idx] = copia[i];
    }
    memcpy(copia, tmp, len);
    return tmp;
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

// Realiza o ciclo de rotações da string informada
char* transforma_string(char* string_entrada, int tamanho) {
    // Preence o vetor string_com_posicao com as linhas rotacionadas
    for (j = 0; j < tamanho; j++) {
        lista_de_strings[j].posicao = j;
        strcpy(lista_de_strings[j].string_rotacionada, desloca_posicao(string_entrada, -j));
    }
    
    // Coloca os textos de string_com_posicaos em ordem alfabética
    qsort(lista_de_strings, tamanho, sizeof(struct string_com_posicao), funcao_comparacao);
    
    //Serial.println(lista_de_strings[3].string_rotacionada);
    memset(string_rotacionada, 0, sizeof(string_rotacionada));
    for (k = 0; k < strlen(string_entrada); k++) {
        string_rotacionada[k] = lista_de_strings[k].string_rotacionada[tamanho-1];
    }
    return string_rotacionada;
}
/*
// Método de Burrows - Wheeler
char* burrows_wheeler(char* string_entrada) {
    int tamanho = strlen(string_entrada);

    // Realiza as rotações da string original
    char* transformada_burrows_wheeler = transforma_string(string_entrada, tamanho);
    
    return transformada_burrows_wheeler;
}*/

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Olá");
  if(Serial.available() > 0){
    recebi = "";
    recebi = Serial.readStringUntil('\n');
    if(recebi.length() > 33){
      Serial.println("Máximo de 33 caracteres!");
    }else{
      recebi.toCharArray(string_entrada, recebi.length() + 1);
      strcat(string_entrada, "$");
      Serial.print("Texto a ser tranformado: ");
      Serial.println(string_entrada);
      Serial.print("Método de Burrows-Wheeler: ");
      Serial.println(transforma_string(string_entrada, strlen(string_entrada)));
    }
  }
}
