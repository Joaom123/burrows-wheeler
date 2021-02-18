/*
   @(#)burrows-wheeler.ino

   Copyright 2019 by Anureet Kaur,
   Geeks for geeks ORG
   Free source-code.

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
#include "burrows-wheeler.h"

void setup() {
  Serial.begin(9600); // Configurando para 9600 o baud rate da Serial do Arduino
}

void loop() {
  if (Serial.available() > 0) {
    memset(string_entrada, 0, sizeof(string_entrada));
    Serial.readBytesUntil('\n', string_entrada, TAMANHO_MAXIMO_DA_ENTRADA);

    if (strlen(string_entrada) > TAMANHO_MAXIMO_DA_ENTRADA - 2) { // -2 por conta do '$' e do '\0'
      Serial.print("Máximo de ");
      Serial.print(TAMANHO_MAXIMO_DA_ENTRADA + 1);
      Serial.println(" caracteres!");
    } else {
      strcat(string_entrada, "$"); // Concatena '$' ao final da string, usado na etapa de verificação.
      Serial.print("Texto a ser tranformado: ");
      Serial.println(string_entrada);
      Serial.print("Método de Burrows-Wheeler: ");
      burrows_wheeler(); // Execução da transformação
      Serial.println(string_rotacionada);
    }
  }
}
