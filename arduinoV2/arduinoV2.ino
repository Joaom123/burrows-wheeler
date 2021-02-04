#define TAMANHO_MAXIMO_DA_ENTRADA 36

void setup() {
  Serial.begin(9600);
}

// vetor que armazena os dados vindos da Serial
char string_entrada[TAMANHO_MAXIMO_DA_ENTRADA];

//vetor temporário que armazena o deslocamentos
char tmp[TAMANHO_MAXIMO_DA_ENTRADA] = "";

// string de copia para não afetar a original
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
char string_rotacionada[TAMANHO_MAXIMO_DA_ENTRADA];

int len, new_idx;
int i = 0, j = 0, k = 0;
int qtd_posicoes = 0;

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
    //return tmp;
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
    (Serial.readStringUntil('\n')).toCharArray(string_entrada, TAMANHO_MAXIMO_DA_ENTRADA + 1);
    // -2 Por conta do $ e do \0
    if(strlen(string_entrada) > TAMANHO_MAXIMO_DA_ENTRADA - 2){
      Serial.print("Máximo de ");
      Serial.print(TAMANHO_MAXIMO_DA_ENTRADA - 2);
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
