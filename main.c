/*
 * @(#)burrows-wheeler.c
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
-------------------------------------------------------------
--  #2.
--  Date: Dec, 11, 2020
--  Author: Elysson Gabriel e João Marcus
--  Motivo: Trabalho da disciplina de
			Sistemas Embarcados 2020.2, Professor: Elias Teodoro
-------------------------------------------------------------
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "burrows-wheeler.h"

int main() {
	// Realiza a leitura da entrada
    char string_entrada[45];
    printf("Digite um texto de no máximo 44 caracteres: ");
    scanf("%[^\n]", string_entrada);
    // A tranformada de burrows-wheeler também funciona sem o $, porém concatemos a string original
    // devido ao nosso meio de validação, que realiza a transformada inversa utilizando o ‘$’ como EOF.
    strcat(string_entrada, "$");
    printf("Texto a ser tranformado: %s\n", string_entrada);
    // Chama o BWT, passando a entrada como parâmetro
    char* string_saida = burrows_wheeler(string_entrada);
    // Mostra o resultado da transformada
    printf("Método de Burrows-Wheeler: %s\n", string_saida);
}
