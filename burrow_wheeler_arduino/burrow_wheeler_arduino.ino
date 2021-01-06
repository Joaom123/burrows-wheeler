#include "burrow_wheeler.h" // Algoritmo de Burrow-Wheeler
#define TAMANHO_MAXIMO_DA_ENTRADA 35

char entrada[36];
char* saida;
unsigned long tempoAntesDaTransformada;
unsigned long tempoDepoisDaTransformada;

// Imprime o texto da entrada
void imprime_entrada() {
  Serial.print("Texto a ser transformado: ");
  Serial.println(entrada);
}

// Imprime o texto da saída
void imprime_saida() {
  Serial.print("Método de Burrows-Wheeler: ");
  Serial.println(saida);
}

// Calcula o tempo gasto e imprime-o
void calcula_e_imprime_o_tempo_gasto() {
  Serial.print("O tempo gasto pela transformada foi: ");
  Serial.print(tempoDepoisDaTransformada - tempoAntesDaTransformada);
  Serial.println(" ms");
}

// Guarda o tempo antes da transformada
void pega_tempo_antes_da_transformada() {
  tempoAntesDaTransformada = millis();
}

// Guarda o tempo após a transformada
void pega_tempo_depois_da_transformada() {
  tempoDepoisDaTransformada = millis();
}

// Pega a entrada da serial, em String, e transforma-a em array de char
void pega_entrada_e_transforma_string_em_array_de_char() {
  String entradaDaSerial = Serial.readString();
  entradaDaSerial.toCharArray(entrada, 37);
}

// Prepara a entrada para a validação de corretude
void prepara_entrada() {
  strcat(entrada, "$"); // concatena $ ao final da entrada
}

// Guarda o resultado da transformada de burrows-wheeler
void transformada_burrows_wheeler() {
  saida = burrows_wheeler(entrada);
}

void imprime_validacao_do_tamanho_da_entrada() {
    Serial.print("O tamanho máximo de ");
    Serial.print(TAMANHO_MAXIMO_DA_ENTRADA);
    Serial.println(" caracteres foi atingido!");
}

bool entrada_eh_maior_que_o_permitido() {
  return strlen(entrada) > TAMANHO_MAXIMO_DA_ENTRADA;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    pega_entrada_e_transforma_string_em_array_de_char();
    
    if(entrada_eh_maior_que_o_permitido()) {
      imprime_validacao_do_tamanho_da_entrada();
      return;
    }
    
    imprime_entrada();
    prepara_entrada();
    pega_tempo_antes_da_transformada();
    transformada_burrows_wheeler();
    pega_tempo_depois_da_transformada();
    imprime_saida();
    calcula_e_imprime_o_tempo_gasto();
  }
}
