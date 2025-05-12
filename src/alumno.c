/*********************************************************************************************************************
Copyright (c) 2025, Bayona Franco Gabriel <gabrielbayona19@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file alumno.c
 ** @brief Implementación del módulo para manejo de datos de alumnos
 **/

/* === Headers files inclusions ==================================================================================== */
#include <string.h>
#include <stdio.h>
#include "alumno.h"

/* === Macros definitions ========================================================================================== */
#define MAX_STRING 128

/* === Private function declarations =============================================================================== */
/**
 * @brief Función interna para serializar los campos de texto.
 * 
 * @param campo Nombre del campo
 * @param valor Valor del campo
 * @param destino Buffer donde se almacenará el resultado
 * @param pos Puntero a la posición actual en el buffer
 */
static void SerializarTexto(const char *campo, const char *valor, char *destino, size_t *pos) {
    *pos += snprintf(destino + *pos, 100, "\"%s\":\"%s\",", campo, valor);
}
 

/**
 * @brief Función interna para serializar los campos numéricos.
 * 
 * @param campo Nombre del campo
 * @param valor Valor numérico del campo
 * @param destino Buffer donde se almacenará el resultado
 * @param pos Puntero a la posición actual en el buffer
 */
static void SerializarNumero(const char *campo, int valor, char *destino, size_t *pos) {
    *pos += snprintf(destino + *pos, 100, "\"%s\":%d,", campo, valor);
}



/* === Public function implementation ============================================================================== */
/**
 * @brief Serializa un Alumno a formato JSON.
 * 
 * @param alumno Puntero al alumno a serializar
 * @param resultado Buffer donde se almacenará el JSON
 * @param espacio_disponible Espacio disponible en el buffer
 * @return int Longitud de la cadena generada o -1 si no hay espacio suficiente
 */
int Serializar(const alumno_t *alumno, char *resultado, size_t espacio_disponible) {
    if (espacio_disponible < 100) return -1;  // Validamos que haya suficiente espacio

    size_t pos = 0;

    // Comienza el objeto JSON
    pos += snprintf(resultado + pos, espacio_disponible, "{");

    // Serializa los campos del alumno
    SerializarTexto("nombre", alumno->nombre, resultado, &pos);
    SerializarTexto("apellido", alumno->apellido, resultado, &pos);
    SerializarNumero("documento", alumno->documento, resultado, &pos);

    // Elimina la última coma y cierra el objeto JSON
    resultado[pos - 1] = '}'; // Eliminar la última coma
    resultado[pos] = '\0';    // Finalizar la cadena

    return pos;
}