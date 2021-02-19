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
// #include "burrows-wheeler-lib.h"
#include "burrows-wheeler-lib-otimizado.h"
#include "medicoes.h"

int main()
{
    printf("Digite um texto de no máximo %d caracteres: ", TAMANHO_MAXIMO_DA_ENTRADA);
    scanf("%[^\n]", string_entrada);
    // A tranformada de burrows-wheeler também funciona sem o $, porém concatemos a string original
    // devido ao nosso meio de validação, que realiza a transformada inversa utilizando o ‘$’ como EOF.
    strcat(string_entrada, "$");
    printf("Texto a ser tranformado: %s\n", string_entrada);

    pega_tempo_antes_da_execucao();
    burrows_wheeler(); // Execução da transformada
    pega_tempo_depois_da_execucao();

    printf("Método de Burrows-Wheeler: %s\n", string_rotacionada);
    calcula_e_exibe_duracao();
}
