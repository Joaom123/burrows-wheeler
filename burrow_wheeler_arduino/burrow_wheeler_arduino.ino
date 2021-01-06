#include "burrow_wheeler.h" // Algoritmo de Burrow-Wheeler

char entrada[36];
char* saida;
unsigned long tempoAntesDaTransformada;
unsigned long tempoDepoisDaTransformada;

//
void imprime_entrada() {
  Serial.print("Texto a ser transformado: ");
  Serial.println(entrada);
}

//
void imprime_saida() {
  Serial.print("Método de Burrows-Wheeler: ");
  Serial.println(saida);
}

//
void calcula_e_imprime_o_tempo_gasto() {
  Serial.print("O tempo gasto pela transformada foi: ");
  Serial.print(tempoDepoisDaTransformada - tempoAntesDaTransformada);
  Serial.println(" ms");
}

//
void pega_tempo_antes_da_transformada() {
  tempoAntesDaTransformada = millis();
}

//
void pega_tempo_depois_da_transformada() {
  tempoDepoisDaTransformada = millis();
}

//
void pega_entrada_e_transforma_string_em_array_de_char() {
  String entradaDaSerial = Serial.readString();
  entradaDaSerial.toCharArray(entrada, 37);
}

//
void prepara_entrada() {
  strcat(entrada, "$"); // concatena $ ao final da entrada
}

//
void transformada_burrows_wheeler() {
  saida = burrows_wheeler(entrada);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    pega_entrada_e_transforma_string_em_array_de_char();
    //TODO: Impedir uma entradar maior que o permitido
    imprime_entrada();
    prepara_entrada();
    pega_tempo_antes_da_transformada();
    transformada_burrows_wheeler();
    pega_tempo_depois_da_transformada();
    imprime_saida();
    calcula_e_imprime_o_tempo_gasto();
  }
}
